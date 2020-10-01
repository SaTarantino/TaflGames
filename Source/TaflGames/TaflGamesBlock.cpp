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
	//TArray<int32> GameGrid = this->OwningGrid->getCoordinateArray();
}

// The block just clicked.
void ATaflGamesBlock::BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{
	if (!this->bIsOccupied && PlayerPawn->SelectedPiece != nullptr)
	{
		PlayerPawn->SelectedBlock = this;
		PlayerPawn->SelectedPiece->OwningBlock->bIsOccupied = false;

		HandleClicked();
	}
	else
	{
		return;
	}
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
		int selectedBlockColumn = PlayerPawn->SelectedBlock->column;
		int selectedBlockRow = PlayerPawn->SelectedBlock->row;

		/*if (bIsOccupied == false)
			return;*/

		if (pieceColumn == column || pieceRow == row)
		{
			// Get the location of the new block
			const FVector NewLocation = PlayerPawn->SelectedBlock->GetActorLocation();

			// TODO:
			// 1: Check if there are other pieces in the way


			//// Check if there is a piece in the same Column
			//if (pieceColumn == selectedBlockColumn)
			//{
			//	if (pieceColumn < selectedBlockColumn)
			//	{
			//		for (int i = (selectedBlockColumn - pieceColumn) - 1; i = 0; i--)
			//		{
			//			if ()
			//		}
			//	}
			//}
			//// Checl of tjere is a pice in the same Row
			//else
			//{
			//	
			//}
			
			// Move the Piece in the new location
			PlayerPawn->SelectedPiece->SetActorLocation(NewLocation);

			PlayerPawn->SelectedPiece->OwningBlock = PlayerPawn->SelectedBlock;
			PlayerPawn->SelectedPiece->OwningBlock->bIsOccupied = true;
			PlayerPawn->SelectedBlock->bIsOccupied = true;

			//this->HighlightBlock(false);
			//PlayerPawn->SelectedPiece->HighlightPiece(false);
			//PlayerPawn->SelectedPiece = nullptr;
			
			// Set the block and piece back to the their original color
			this->HighlightBlock(false);
			PlayerPawn->SelectedPiece->PieceClicked(PlayerPawn->SelectedPiece->GetPieceMesh(), FKey("LeftMouseClick"));
			
		}
		else
		{
			return;
		}
	}
}

void ATaflGamesBlock::HighlightBlock(bool bOn)
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
