#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TaflGamesBlock.h"
#include "TaflGamesPiece.h"
#include "TaflGamesPawn.generated.h"

/*

*/

UCLASS(config = Game)
class ATaflGamesPawn : public APawn
{
	GENERATED_UCLASS_BODY()

public:
	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void CalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult) override;

public:
	bool isPieceSelected;

protected:
	void TriggerClick();
	void ReleaseClick();
	void TraceForBlock(const FVector& Start, const FVector& End, bool bDrawDebugHelpers);
	void TraceForPiece(const FVector& Start, const FVector& End, bool bDrawDebugHelpers);

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	class ATaflGamesBlock* CurrentBlockFocus;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	class ATaflGamesPiece* CurrentPieceFocus;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	class ATaflGamesPiece* SelectedPiece;

public:
	FORCEINLINE bool getIsPieceSelected() { return isPieceSelected; }
};
