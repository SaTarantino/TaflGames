#include "TaflGamesPawn.h"
#include "TaflGamesBlock.h"
#include "TaflGamesPiece.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

ATaflGamesPawn::ATaflGamesPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	isPieceSelected = false;
}

void ATaflGamesPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
		{
			if (UCameraComponent* OurCamera = PC->GetViewTarget()->FindComponentByClass<UCameraComponent>())
			{
				FVector Start = OurCamera->GetComponentLocation();
				FVector End = Start + (OurCamera->GetComponentRotation().Vector() * 8000.0f);
				TraceForPiece(Start, End, true);
				TraceForBlock(Start, End, true);
			}
		}
		else
		{
			FVector Start, Dir, End;
			PC->DeprojectMousePositionToWorld(Start, Dir);
			End = Start + (Dir * 8000.0f);
			TraceForBlock(Start, End, false);
			TraceForPiece(Start, End, false);
		}
	}
}

void ATaflGamesPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("TriggerClick", EInputEvent::IE_Pressed, this, &ATaflGamesPawn::TriggerClick);
	PlayerInputComponent->BindAction("ClickDown", EInputEvent::IE_Released, this, &ATaflGamesPawn::ReleaseClick);
}

void ATaflGamesPawn::CalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult)
{
	Super::CalcCamera(DeltaTime, OutResult);

	OutResult.Rotation = FRotator(-90.0f, -90.0f, 0.0f);
}

void ATaflGamesPawn::TriggerClick()
{
	/*if (CurrentPieceFocus)
	{
		CurrentPieceFocus->HandleClicked();
	}*/
}

void ATaflGamesPawn::ReleaseClick()
{
}

void ATaflGamesPawn::TraceForPiece(const FVector& Start, const FVector& End, bool bDrawDebugHelpers)
{
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility);
	if (bDrawDebugHelpers)
	{
		DrawDebugLine(GetWorld(), Start, HitResult.Location, FColor::Blue);
		DrawDebugSolidBox(GetWorld(), HitResult.Location, FVector(20.0f), FColor::Blue);
	}
	if (HitResult.Actor.IsValid())
	{
		ATaflGamesPiece* HitPiece = Cast<ATaflGamesPiece>(HitResult.Actor.Get());
		if (CurrentPieceFocus != HitPiece)
		{
			if (CurrentPieceFocus)
			{
				CurrentPieceFocus->Highlight(false);
			}
			if (HitPiece)
			{
				HitPiece->Highlight(true);
			}
			CurrentPieceFocus = HitPiece;
		}
	}
	else if (CurrentPieceFocus)
	{
		CurrentPieceFocus->Highlight(false);
		CurrentPieceFocus = nullptr;
	}
}

void ATaflGamesPawn::TraceForBlock(const FVector& Start, const FVector& End, bool bDrawDebugHelpers)
{
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility);
	if (bDrawDebugHelpers)
	{
		DrawDebugLine(GetWorld(), Start, HitResult.Location, FColor::Red);
		DrawDebugSolidBox(GetWorld(), HitResult.Location, FVector(20.0f), FColor::Red);
	}
	if (HitResult.Actor.IsValid())
	{
		ATaflGamesBlock* HitBlock = Cast<ATaflGamesBlock>(HitResult.Actor.Get());
		if (CurrentBlockFocus != HitBlock)
		{
			if (CurrentBlockFocus)
			{
				CurrentBlockFocus->Highlight(false);
			}
			if (HitBlock)
			{
				HitBlock->Highlight(true);
			}
			CurrentBlockFocus = HitBlock;
		}
	}
	else if (CurrentBlockFocus)
	{
		CurrentBlockFocus->Highlight(false);
		CurrentBlockFocus = nullptr;
	}
}