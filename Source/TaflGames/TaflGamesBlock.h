#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TaflGamesBlock.generated.h"

/** A block that can be clicked */
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

	/** Are we currently active? */
	bool bIsActive;

	/** Pointer to white material used on the focused block */
	UPROPERTY()
	class UMaterial* BaseMaterial;

	/*UPROPERTY()
	class UMaterialInstance* M_Wood_Oak;*/

	UPROPERTY()
	class UMaterialInstance* OrangeMaterial;

	UPROPERTY()
	class UMaterialInstance* BlueMaterial;

	/** Grid that owns us */
	UPROPERTY()
	class ATaflGamesBlockGrid* OwningGrid;

	/** Handle the block being clicked */
	UFUNCTION()
	void BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);

	void HandleClicked();

	void Highlight(bool bOn);

public:
	/** Returns DummyRoot subobject **/
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
	/** Returns BlockMesh subobject **/
	FORCEINLINE class UStaticMeshComponent* GetBlockMesh() const { return BlockMesh; }
};
