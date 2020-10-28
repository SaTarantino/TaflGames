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
};
