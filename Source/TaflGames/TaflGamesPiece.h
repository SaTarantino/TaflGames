#pragma once

#include "CoreMinimal.h"
#include "TaflGamesPawn.h"
#include "GameFramework/Actor.h"
#include "TaflGamesPiece.generated.h"

/*

*/

UCLASS()
class TAFLGAMES_API ATaflGamesPiece : public AActor
{
	GENERATED_BODY()

	UPROPERTY(Category = Piace, VisibleDefaultsOnly, meta = (AllowPrivateAccess = "ture"))
	class USceneComponent* PieceRoot;

	UPROPERTY(Category = Piace, VisibleDefaultsOnly, meta = (AllowPrivateAccess = "ture"))
	class UStaticMeshComponent* PieceMesh;

public:
	ATaflGamesPiece();

	bool bIsActive;

	/* Pointer to the white material used on the focussed block */
	UPROPERTY()
	class UMaterial* BaseMaterial;

	/* Pointer to the color used on the select */
	UPROPERTY()		
	class UMaterialInstance* BlueMaterial;

	UPROPERTY()
	class UMaterialInstance* OrangeMaterial;

	/*UPROPERTY()
	class ATaflGamesBlockGrid* OwningGrid;*/

	UPROPERTY()
	class ATaflGamesBlock* OwningBlock;

	UPROPERTY()
	class ATaflGamesPawn* PlayerPawn;

public:
	UFUNCTION()
	void PiaceClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);

	void HandleClicked();

	void Highlight(bool isActive);

public:
	FORCEINLINE class USceneComponent* GetPieceRoot() const { return PieceRoot; }
	FORCEINLINE class UStaticMeshComponent* GetPieceMesh() const { return PieceMesh; }
	FORCEINLINE class ATaflGamesBlock* GetOwingBlock() const { return OwningBlock; }
};
