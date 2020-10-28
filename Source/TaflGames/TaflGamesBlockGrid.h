#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TaflGamesBlockGrid.generated.h"

// Class used to spawn blocks
UCLASS(minimalapi)
class ATaflGamesBlockGrid : public AActor
{
	GENERATED_BODY()

	// Dummy root component
	UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DummyRoot;

public:
	ATaflGamesBlockGrid();

	// Number of blocks along each side of grid
	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
	int32 Size;

	// Spacing of blocks
	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
	float BlockSpacing;

	TArray<int32> coordinateArray;	
	
protected:
	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface

	//void SetRowAndColumn(int countRow, int countColumn, int size);

public:

	// Returns DummyRoot subobject
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }

	//FORCEINLINE TArray<int32> getCoordinateArray() const { return coordinateArray; }
};
