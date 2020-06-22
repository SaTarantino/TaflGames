#include "TaflGamesBlock.h"
#include "TaflGamesBlockGrid.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"
#include "Kismet/GameplayStatics.h"

ATaflGamesBlock::ATaflGamesBlock()
{
	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> BaseMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> BlueMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> OrangeMaterial;
		FConstructorStatics()
			: PlaneMesh(TEXT("/Game/Puzzle/Meshes/PuzzleCube.PuzzleCube"))
			, BaseMaterial(TEXT("/Game/Puzzle/Meshes/BaseMaterial.BaseMaterial"))
			, OrangeMaterial(TEXT("/Game/Puzzle/Meshes/OrangeMaterial.OrangeMaterial"))
			, BlueMaterial(TEXT("/Game/Puzzle/Meshes/BlueMaterial.BlueMaterial"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Create static mesh component
	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh0"));
	BlockMesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());
	BlockMesh->SetRelativeScale3D(FVector(1.f, 1.f, 0.f));
	BlockMesh->SetRelativeLocation(FVector(0.f, 0.f, 25.f));
	BlockMesh->SetMaterial(0, ConstructorStatics.OrangeMaterial.Get());
	BlockMesh->SetupAttachment(DummyRoot);
	BlockMesh->OnClicked.AddDynamic(this, &ATaflGamesBlock::BlockClicked);

	// Save a pointer to the orange material. USATO nel caso serva cambiare colore ai blocchi.
	BaseMaterial = ConstructorStatics.BaseMaterial.Get();
	OrangeMaterial = ConstructorStatics.OrangeMaterial.Get();
	BlueMaterial = ConstructorStatics.BlueMaterial.Get();

	PlayerPawn = Cast<ATaflGamesPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void ATaflGamesBlock::BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{
	HandleClicked();
}

void ATaflGamesBlock::HandleClicked()
{
	// Check we are not already active
	//if (!bIsActive)
	//{
	//	bIsActive = true;

	//	// Change material
	//	BlockMesh->SetMaterial(0, BlueMaterial);

	//	// Tell the Grid
	//	/*if (OwningGrid != nullptr)
	//	{
	//		OwningGrid->AddScore();
	//	}*/
	//}
}

void ATaflGamesBlock::Highlight(bool bOn)
{
	if (PlayerPawn)
	{
		if (PlayerPawn->SelectedPiece)
		{
			if (bOn)
			{
				BlockMesh->SetMaterial(0, BaseMaterial);
			}
			else
			{
				BlockMesh->SetMaterial(0, OrangeMaterial);
			}
		}
	}
}
