#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TaflGamesGameMode.generated.h"

/** GameMode class to specify pawn and playercontroller */
UCLASS(minimalapi)
class ATaflGamesGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATaflGamesGameMode();
	ATaflGamesGameMode* GM;
	TArray<int>* spawn = new TArray<int>;
};
