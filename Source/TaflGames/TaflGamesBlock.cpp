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
			a = columnMove();
			GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Red, FString::Printf(TEXT("%i"), (a)));
			

			// Move the Piece in the new location
			PlayerPawn->SelectedPiece->SetActorLocation(NewLocation);

			PlayerPawn->SelectedPiece->OwningBlock = PlayerPawn->SelectedBlock;
			PlayerPawn->SelectedPiece->HandleIndexs(
			PlayerPawn->SelectedBlock->index, PlayerPawn->SelectedBlock->column, PlayerPawn->SelectedBlock->row);
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

int ATaflGamesBlock::columnMove()
{
	ATaflGamesGameMode* GameMode = Cast<ATaflGamesGameMode>(GetWorld()->GetAuthGameMode());
	TArray<ATaflGamesBlock*> arr;
	int i = 0;

	if (PlayerPawn->SelectedPiece->columnPiece == PlayerPawn->SelectedBlock->column)
	{
		for (int32 j = 0; j < GameMode->blockArray.Num(); j++)
		{
			if (GameMode->blockArray[j]->column == PlayerPawn->SelectedPiece->columnPiece)
			{
				if (PlayerPawn->SelectedPiece->indexPiece < PlayerPawn->SelectedBlock->index)
				{
					if (GameMode->blockArray[j]->row > PlayerPawn->SelectedPiece->rowPiece &&
						GameMode->blockArray[j]->row <= PlayerPawn->SelectedBlock->row)
					{
						arr.Add(GameMode->blockArray[j]);
					}
				}
				else if (PlayerPawn->SelectedPiece->indexPiece > PlayerPawn->SelectedBlock->index)
				{
					if (GameMode->blockArray[j]->row < PlayerPawn->SelectedPiece->rowPiece &&
						GameMode->blockArray[j]->row >= PlayerPawn->SelectedBlock->row)
					{
						arr.Add(GameMode->blockArray[j]);
					}
				}
			}
		}
	}

	/*for (int32 y = 0; y < arr.Num(); y++)
	{
		GEngine->AddOnScreenDebugMessage(-1, 120.f, FColor::Red,
			FString::Printf(TEXT("%i"), arr[y]->index));
	}*/

	for (int32 l = 0; l < arr.Num(); l++)
	{
		if (arr[l]->bIsOccupied)
		{
			i = -1;
			return i;
		}
		else
			i = 1;
	}

	return i;
}

int ATaflGamesBlock::rowMove()
{
	if (PlayerPawn->SelectedPiece->rowPiece == PlayerPawn->SelectedBlock->row)
	{
		if (PlayerPawn->SelectedPiece->indexPiece > PlayerPawn->SelectedBlock->index)
		{
			
		}
		else if (PlayerPawn->SelectedPiece->indexPiece < PlayerPawn->SelectedBlock->index)
		{
			//TODO
		}
	}
}
