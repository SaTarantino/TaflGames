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


			/*GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue,
				FString::Printf(TEXT("%s"), checkColumn(pieceColumn, selectedBlockColumn)));
			*/
			//columnMove(pieceColumn, selectedBlockColumn, pieceRow)

			//for (TObjectIterator<ATaflGamesBlockGrid> Grid; Grid; ++Grid)
			//{
			//	/*if (Grid->IsA(ATaflGamesBlockGrid::StaticClass))
			//	{
			//	}*/

			//	if (Grid)
			//	{
			//		/*for (int i = 0; i < Grid->coordinateArray.Num(); i++)
			//		{
			//			
			//		}*/
			//	}
			//}

			// TODO:
			// 1: Check if there are other pieces in the way

			// Move the Piece in the new location
			PlayerPawn->SelectedPiece->SetActorLocation(NewLocation);

			PlayerPawn->SelectedPiece->OwningBlock = PlayerPawn->SelectedBlock;
			PlayerPawn->SelectedPiece->indexPiece = PlayerPawn->SelectedBlock->index;
			PlayerPawn->SelectedPiece->OwningBlock->bIsOccupied = true;
			PlayerPawn->SelectedBlock->bIsOccupied = true;

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

void ATaflGamesBlock::columnMove(int pieceColumn, int selectedBlockColumn, int pieceRow)
{
	if (pieceColumn < selectedBlockColumn)
	{
		/*for (int i = pieceColumn; i < selectedBlockColumn; i++)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue,
				FString::Printf(TEXT("Row: %i"), );
		}*/

		//checkColumn(pieceColumn, pieceRow);

	}
	/*else if (pieceColumn > selectedBlockColumn)
	{

	}*/
}

//bool ATaflGamesBlock::checkColumn(int column, int row)
//{
//	//for (TObjectIterator<ATaflGamesBlockGrid> Grid; Grid; ++Grid)
//	//{
//	//	if (Grid)
//	//	{
//	//		for (TObjectIterator<ATaflGamesBlock> Block; Block; ++Block)
//	//		{
//	//			if (Block)
//	//			{
//	//				if (Block->index < PlayerPawn->SelectedPiece->OwningBlock->index)
//	//				{
//	//					if (Block->row != PlayerPawn->SelectedPiece->OwningBlock->row)
//	//					{
//	//						if
//	//					}
//	//				}
//	//				// Move in the square above
//	//				else if (Block->index > PlayerPawn->SelectedPiece->OwningBlock->index)
//	//				{
//
//	//				}
//	//			}
//	//		}
//	//	}
//	//}
//	//return false;
//
//	// Verso Giu
//	if (PlayerPawn->SelectedBlock->index < PlayerPawn->SelectedPiece->OwningBlock->index)
//	{
//		int indexArrivo = PlayerPawn->SelectedBlock->index;
//
//		if ((PlayerPawn->SelectedPiece->indexPiece - 9))
//	}
//}
