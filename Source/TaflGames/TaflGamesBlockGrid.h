#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TaflGamesBlockGrid.generated.h"

/** Class used to spawn blocks and manage score */
UCLASS(minimalapi)
class ATaflGamesBlockGrid : public AActor
{
	GENERATED_BODY()

	/** Dummy root component */
	UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DummyRoot;

	/** Text component for the score */
	/*UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UTextRenderComponent* ScoreText;*/

public:
	ATaflGamesBlockGrid();

	/** Number of blocks along each side of grid */
	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
	int32 Size;

	/** Spacing of blocks */
	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
	float BlockSpacing;

protected:
	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface

public:

	/** Returns DummyRoot subobject **/
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
	/** Returns ScoreText subobject **/
	//FORCEINLINE class UTextRenderComponent* GetScoreText() const { return ScoreText; }
};
