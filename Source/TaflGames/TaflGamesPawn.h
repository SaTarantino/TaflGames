#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TaflGamesPawn.generated.h"

UCLASS(config = Game)
class ATaflGamesPawn : public APawn
{
	GENERATED_UCLASS_BODY()

public:

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void CalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult) override;

protected:
	void TriggerClick();
	void TraceForBlock(const FVector& Start, const FVector& End, bool bDrawDebugHelpers);

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		class ATaflGamesBlock* CurrentBlockFocus;
};
