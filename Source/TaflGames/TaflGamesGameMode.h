#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TaflGamesPiece.h"
#include "TaflGamesGameMode.generated.h"

/** GameMode class to specify pawn and playercontroller */
UCLASS(minimalapi)
class ATaflGamesGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATaflGamesGameMode();

	/*	
		Tablut was the Sápmi tafl variant played on a 9x9 board,
		with a king and eight defenders against sixteen attackers.
		
		O O O X X X O O O
		O O O O X O O O O
		O O O O V O O O O
		X O O O V O O O X
		X X V V K V V X X
		X O O O V O O O X
		O O O O V O O O O
		O O O O X O O O O
		O O O X X X O O O

		O = empty blocks
		X = attackers
		V = defenders
		K = king
	*/
	ATaflGamesGameMode* Tablut;
	TArray<int>* spawn = new TArray<int>;
	TArray<ATaflGamesPiece*> pieceArray;
	TArray<ATaflGamesBlock*> blockArray;

	// COLUMNS:
	TArray<ATaflGamesBlock*> c1;
	TArray<ATaflGamesBlock*> c2;
	TArray<ATaflGamesBlock*> c3;
	TArray<ATaflGamesBlock*> c4;
	TArray<ATaflGamesBlock*> c5;
	TArray<ATaflGamesBlock*> c6;
	TArray<ATaflGamesBlock*> c7;
	TArray<ATaflGamesBlock*> c8;
	TArray<ATaflGamesBlock*> c9;

	// ROWS:
	TArray<ATaflGamesBlock*> r1;
	TArray<ATaflGamesBlock*> r2;
	TArray<ATaflGamesBlock*> r3;
	TArray<ATaflGamesBlock*> r4;
	TArray<ATaflGamesBlock*> r5;
	TArray<ATaflGamesBlock*> r6;
	TArray<ATaflGamesBlock*> r7;
	TArray<ATaflGamesBlock*> r8;
	TArray<ATaflGamesBlock*> r9;
};
