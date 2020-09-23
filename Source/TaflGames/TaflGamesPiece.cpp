#include "TaflGamesPiece.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATaflGamesPiece::ATaflGamesPiece()
{
	//Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = false;

	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> Shape_Cylinder;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> BaseMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> BlueMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> OrangeMaterial;
		FConstructorStatics()
			: Shape_Cylinder(TEXT("/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder"))
			, BaseMaterial(TEXT("/Game/Puzzle/Meshes/BaseMaterial.BaseMaterial"))
			, BlueMaterial(TEXT("/Game/Puzzle/Meshes/BlueMaterial.BlueMaterial"))
			, OrangeMaterial(TEXT("/Game/Puzzle/Meshes/OrangeMaterial.OrangeMaterial"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	PieceRoot = CreateDefaultSubobject<USceneComponent>(TEXT("PieceRoot0"));
	RootComponent = PieceRoot;

	PieceMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PiaceMesh0"));
	PieceMesh->SetStaticMesh(ConstructorStatics.Shape_Cylinder.Get());
	PieceMesh->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));
	PieceMesh->SetRelativeLocation(FVector(0.f, 0.f, 25.f));
	PieceMesh->SetMaterial(0, ConstructorStatics.BlueMaterial.Get());
	PieceMesh->SetupAttachment(PieceRoot);
	PieceMesh->OnClicked.AddDynamic(this, &ATaflGamesPiece::PiaceClicked);

	// Save a pointer to the orange material.
	BaseMaterial = ConstructorStatics.BaseMaterial.Get();
	BlueMaterial = ConstructorStatics.BlueMaterial.Get();
	OrangeMaterial = ConstructorStatics.OrangeMaterial.Get();

	PlayerPawn = Cast<ATaflGamesPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void ATaflGamesPiece::PiaceClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{
	if (PlayerPawn)
	{
		/* If there is no Piece selected: */
		if (!PlayerPawn->SelectedPiece)
		{
			/* 
				Call HandleClicked function in order to select the pice,
				then save this piece as the Selected Piece.
			*/
			HandleClicked();
			PlayerPawn->SelectedPiece = this;
		}
		/* If there is a pice selected: */
		else if (PlayerPawn->SelectedPiece)
		{
			/* If the selected piece IS DIFFERENT to this piece (the piece just selected): */
			if (PlayerPawn->SelectedPiece != this)
			{
				/* 
					Call HandleClicked function to the saved SelectedPiece in order to deselect it,
					then set the piece just clicked as the SelectedPiece,
					and then call the HandleClicked function in order to select it.
				*/
				PlayerPawn->SelectedPiece->HandleClicked();
				PlayerPawn->SelectedPiece = this;
				HandleClicked();
			}
			/* Else if the selected pice IS THE SAME to this piece (the piece just selected): */
			else
			{
				/*
					Call the HandleCliked function in order to deselect this piece,
					save Selected Piece as a null pointer (put it in the garbage collector).
				*/
				HandleClicked();
				PlayerPawn->SelectedPiece = nullptr;
			}
		}
	}
}

void ATaflGamesPiece::HandleClicked()
{
	if (!bIsActive)
	{
		bIsActive = true;

		PieceMesh->SetMaterial(0, OrangeMaterial);
	}
	else
	{
		bIsActive = false;

		PieceMesh->SetMaterial(0, BlueMaterial);
	}
}

void ATaflGamesPiece::Highlight(bool isActive)
{
	if (bIsActive)
	{
		if (isActive)
		{
			PieceMesh->SetMaterial(0, BaseMaterial);
		}
		else
		{
			PieceMesh->SetMaterial(0, OrangeMaterial);
		}
	}
	else
	{
		if (isActive)
		{
			PieceMesh->SetMaterial(0, BaseMaterial);
		}
		else
		{
			PieceMesh->SetMaterial(0, BlueMaterial);
		}
	}
}
