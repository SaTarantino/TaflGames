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

	UPROPERTY(VisibleAnywhere, Category = Index)
	int indexPiece;

	UPROPERTY(VisibleAnywhere, Category = Index)
	int columnPiece;

	UPROPERTY(VisibleAnywhere, Category = Index)
	int rowPiece;

	/* Pointer to the white material used on the focussed block */
	UPROPERTY()
	class UMaterial* BaseMaterial;

	/* Pointer to the color used on the select */
	UPROPERTY()		
	class UMaterialInstance* BlueMaterial;

	UPROPERTY()
	class UMaterialInstance* OrangeMaterial;

	UPROPERTY()
	class UMaterial* CopperMaterial;

	UPROPERTY()
	class UMaterial* SteelMaterial;

	UPROPERTY()
	class UMaterial* PieceMaterial;

	/*UPROPERTY()
	class ATaflGamesBlockGrid* OwningGrid;*/

	UPROPERTY(VisibleAnywhere, Category = Position)
	class ATaflGamesBlock* OwningBlock;

	UPROPERTY()
	class ATaflGamesPawn* PlayerPawn;

public:
	UFUNCTION()
	void PieceClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);

	void HandleClicked();

	void HighlightPiece(bool isActive);

	void HandleIndexs(int index, int column, int row);

	//void CapturePiece();

	void SetPieceMaterial(UMaterial* pieceMaterial);

public:
	FORCEINLINE class USceneComponent* GetPieceRoot() const { return PieceRoot; }
	FORCEINLINE class UStaticMeshComponent* GetPieceMesh() const { return PieceMesh; }
	FORCEINLINE class ATaflGamesBlock* GetOwingBlock() const { return OwningBlock; }
};
