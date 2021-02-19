#include "TaflGamesBlockGrid.h"
#include "TaflGamesBlock.h"
#include "TaflGamesPiece.h"
#include "TaflGamesGameMode.h"
#include "Components/TextRenderComponent.h"
#include "Engine/World.h"
#include "UObject/Object.h"

#define LOCTEXT_NAMESPACE "PuzzleBlockGrid"

ATaflGamesBlockGrid::ATaflGamesBlockGrid()
{
	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Create static mesh component
	/*ScoreText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ScoreText0"));
	ScoreText->SetRelativeLocation(FVector(200.f, 0.f, 0.1f));
	ScoreText->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));
	ScoreText->SetupAttachment(DummyRoot);*/

	// Set defaults
	Size = 9;
	BlockSpacing = 265.f;
}


void ATaflGamesBlockGrid::BeginPlay()
{
	Super::BeginPlay();

	ATaflGamesGameMode* GameMode = Cast<ATaflGamesGameMode>(GetWorld()->GetAuthGameMode());

	int index = -1;
	int countRow = 1;
	int countColumn = 1;

	// Number of blocks
	const int32 NumBlocks = Size * Size;
	// Loop to spawn each block
	for (int32 BlockIndex = 0; BlockIndex < NumBlocks; BlockIndex++)
	{
		const float XOffset = (BlockIndex / Size) * BlockSpacing; // Divide by dimension
		const float YOffset = (BlockIndex%Size) * BlockSpacing; // Modulo gives remainder

		// Make position vector, offset from Grid location
		const FVector BlockLocation = FVector(XOffset, YOffset, 0.f) + GetActorLocation();
		
		// Spawn a block
		ATaflGamesBlock* NewBlock = GetWorld()->SpawnActor<ATaflGamesBlock>(BlockLocation, FRotator(0, 0, 0));
		NewBlock->index = BlockIndex;
		GameMode->blockArray.Add(NewBlock);
		int c;
		int r;
		
		// The follow code set the row and the column for each block.
		// Set the Row
		if (countColumn != Size)
		{
			NewBlock->row = countRow;
			r = countRow;
		}
		else
		{
			NewBlock->row = countRow;
			r = countRow;
			countRow++;
		}

		// Set the column
		if (countColumn != Size)
		{
			NewBlock->column = countColumn;
			c = countColumn;
			countColumn++;
		}
		else
		{
			NewBlock->column = countColumn;
			c = countColumn;
			countColumn = 1;
		}

		index++;

		// If the index is in the array of the spawn, spawn a pice in that box.
		// Spawn the attacker.
		if (GameMode->spawn->Contains(index))
		{
			ATaflGamesPiece* NewPiece = GetWorld()->SpawnActor<ATaflGamesPiece>(BlockLocation, FRotator(0, 0, 0));
			if (NewPiece != nullptr && NewBlock != nullptr)
			{
				NewPiece->OwningBlock = NewBlock;
				NewPiece->HandleIndexs(NewBlock->index, NewBlock->column, NewBlock->row);
				NewPiece->typePice = 1;
				// Set the Piece Material
				NewPiece->SetPieceMaterial(NewPiece->CopperMaterial);
				NewPiece->PieceMaterial = NewPiece->CopperMaterial;

				GameMode->pieceArray.Add(NewPiece);

				NewBlock->bIsOccupied = true;
			}
		}
		// Spawn the defenders.
		else if (GameMode->spawn_->Contains(index))
		{
			ATaflGamesPiece* NewPiece_ = GetWorld()->SpawnActor<ATaflGamesPiece>(BlockLocation, FRotator(0, 0, 0));
			if (NewPiece_ != nullptr && NewBlock != nullptr)
			{
				NewPiece_->OwningBlock = NewBlock;
				NewPiece_->HandleIndexs(NewBlock->index, NewBlock->column, NewBlock->row);
				NewPiece_->typePice = 2;
				// Set the Piece Material
				NewPiece_->SetPieceMaterial(NewPiece_->SteelMaterial);
				NewPiece_->PieceMaterial = NewPiece_->SteelMaterial;

				GameMode->pieceArray.Add(NewPiece_);

				NewBlock->bIsOccupied = true;
			}
		}
		
		// Tell the block about its owner
		if (NewBlock != nullptr)
		{
			NewBlock->OwningGrid = this;
		}
	}
}

#undef LOCTEXT_NAMESPACE

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
