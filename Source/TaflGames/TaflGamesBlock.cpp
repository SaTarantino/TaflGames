#include "TaflGamesBlock.h"
#include "TaflGamesBlockGrid.h"
#include "TaflGamesGameMode.h"
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
		int blockColumn = PlayerPawn->SelectedBlock->column;
		int blockRow = PlayerPawn->SelectedBlock->row;


		if (pieceColumn == column || pieceRow == row)
		{
			// Get the location of the new block
			const FVector NewLocation = PlayerPawn->SelectedBlock->GetActorLocation();

			ATaflGamesGameMode* GameMode = Cast<ATaflGamesGameMode>(GetWorld()->GetAuthGameMode());

			int a = 0;
			
			if (PlayerPawn->SelectedPiece->GetOwingBlock()->column == PlayerPawn->SelectedBlock->column)
			{
				a = moveUp();
				
				if (a == 1)
				{
					GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Red, FString::Printf(TEXT("%i"), (a)));
				}
				else if (a == 2)
				{
					GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Red, FString::Printf(TEXT("%i"), (a)));
				}
			}


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

int ATaflGamesBlock::moveUp()
{
	ATaflGamesGameMode* GameMode = Cast<ATaflGamesGameMode>(GetWorld()->GetAuthGameMode());

	int b = 0;

	if (PlayerPawn->SelectedPiece->GetOwingBlock()->column == PlayerPawn->SelectedBlock->column)
	{
		int32 j = 9;
		int i = 0;

		for (int32 i = 0; i < GameMode->blockArray.Num(); i++)
		{
			if (GameMode->blockArray[i]->column == PlayerPawn->SelectedPiece->GetOwingBlock()->column)
			{
				if (GameMode->blockArray[i]->index > PlayerPawn->SelectedPiece->indexPiece)
				{
					if (GameMode->blockArray[i]->index < PlayerPawn->SelectedBlock->index)
					{
						if (GameMode->blockArray[i]->bIsOccupied == true)
						{
							b = 1;
							return b;
						}
						else
						{
							b = 2;
						}
					}
				}
			}
		}
	}

	return b;







	//if (PlayerPawn->SelectedBlock->column == PlayerPawn->SelectedPiece->GetOwingBlock()->column)
	//{
	//	for (int32 i = 0; i < GameMode->pieceArray.Num(); i++)
	//	{
	//		/*if (GameMode->pieceArray[i]->indexPiece > PlayerPawn->SelectedPiece->indexPiece && 
	//			GameMode->pieceArray[i]->GetOwingBlock()->column == PlayerPawn->SelectedPiece->GetOwingBlock()->column && 
	//			GameMode->pieceArray[i]->indexPiece < PlayerPawn->SelectedBlock->index)
	//		{
	//			if (GameMode->pieceArray[i]->GetOwingBlock()->bIsOccupied == true)
	//			{
	//				b = false;
	//				return b;
	//			}
	//			else
	//			{
	//				b = true;
	//			}
	//		}*/
	//		
	//		if (GameMode->pieceArray[i]->indexPiece > PlayerPawn->SelectedPiece->indexPiece)
	//		{
	//			if (GameMode->pieceArray[i]->indexPiece < PlayerPawn->SelectedBlock->index)
	//			{
	//				if (GameMode->pieceArray[i]->GetOwingBlock()->column == PlayerPawn->SelectedPiece->GetOwingBlock()->column)
	//				{
	//					if (GameMode->pieceArray[i]->GetOwingBlock()->bIsOccupied == true)
	//					{
	//						b = false;
	//						return b;
	//					}
	//					else
	//					{
	//						b = true;
	//					}
	//				}
	//			}
	//		}

	//	}
	//}
	//return b;
}
