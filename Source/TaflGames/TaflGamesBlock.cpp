#include "TaflGamesBlock.h"
#include "TaflGamesBlockGrid.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Engine/Engine.h"
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
	if (PlayerPawn)
	{
		PlayerPawn->SelectedBlock = this;
	}
	else
	{
		return;
	}

	HandleClicked();
}

void ATaflGamesBlock::HandleClicked()
{
	if (!PlayerPawn->SelectedPiece->GetOwingBlock())
	{
		return;
	}
	else
	{
		int pieceColumn = PlayerPawn->SelectedPiece->GetOwingBlock()->column;
		int pieceRow = PlayerPawn->SelectedPiece->GetOwingBlock()->row;

		if (pieceColumn == column || pieceRow == row)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Orange, FString::Printf(TEXT("Same Column/Row")));

			// Get the location of the new block
			const FVector NewLocation = PlayerPawn->SelectedBlock->GetActorLocation();
			
			// Move the Piece in the new location
			PlayerPawn->SelectedPiece->SetActorLocation(NewLocation);

			// TODO:
			// 1: Check if there are other pieces in the way
			// if not:
			// 2: Move the piece
			// 3: Set the new column and row of the piece
			// else: return
		}
		else
		{
			return;
		}

		/*GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, FString::Printf(TEXT("Piece Column: %i"), pieceColumn));
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, FString::Printf(TEXT("Piece Row: %i"), pieceRow));
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::Printf(TEXT("Column: %i"), column));
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::Printf(TEXT("Row: %i"), row));*/
	}
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
				//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Column: %i"), column));
				//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("Row: %i"), row));

			}
			else
			{
				BlockMesh->SetMaterial(0, OrangeMaterial);
			}
		}
	}
}

// This function should be call to set the row and the column of the block.
// If called it dosen't work, so I implemented the code directly in the Begin Play function in BlockGrid.
// That works quite good and shold not give any problem at all.
//void ATaflGamesBlock::SetRowAndColumn(int countRow, int countColumn, int size)
//{
//	// set the row
//	if (countColumn != size)
//	{
//		row = countRow;
//	}
//	else
//	{
//		row = countRow;
//		countRow++;
//	}
//
//	// set the column
//	if (countColumn != size)
//	{
//		column = countColumn;
//		countColumn++;
//	}
//	else
//	{
//		column = countColumn;
//		countColumn = 1;
//	}
//}
