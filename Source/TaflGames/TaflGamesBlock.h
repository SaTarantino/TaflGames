#pragma once

#include "CoreMinimal.h"
#include "TaflGamesPawn.h"
#include "GameFramework/Actor.h"

#include "TaflGamesBlock.generated.h"

/*

*/

UCLASS(minimalapi)
class ATaflGamesBlock : public AActor
{
	GENERATED_BODY()

	/** Dummy root component */
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DummyRoot;

	/** StaticMesh component for the clickable block */
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BlockMesh;

public:
	ATaflGamesBlock();

	/** Check if is active */
	bool bIsActive;

	UPROPERTY(VisibleAnywhere, Category = Position)
	bool bIsOccupied = false;

	UPROPERTY(VisibleAnywhere, Category = Position)
	int column;

	UPROPERTY(VisibleAnywhere, Category = Position)
	int row;

	UPROPERTY(VisibleAnywhere, Category = Position)
	int index;

	/** Pointer to white material used on the focused block */
	UPROPERTY()
	class UMaterial* BaseMaterial;

	UPROPERTY()
	class UMaterialInstance* OrangeMaterial;

	UPROPERTY()
	class UMaterialInstance* BlueMaterial;

	/** Grid that owns us */
	UPROPERTY()
	class ATaflGamesBlockGrid* OwningGrid;

	UPROPERTY()
	class ATaflGamesPawn* PlayerPawn;

public:
	/** Handle the block being clicked */
	UFUNCTION()
	void BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);

	void HandleClicked();

	void HighlightBlock(bool bOn);

	int columnMove();

	int rowMove();

public:
	/** Returns DummyRoot subobject **/
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
	/** Returns BlockMesh subobject **/
	FORCEINLINE class UStaticMeshComponent* GetBlockMesh() const { return BlockMesh; }
};
