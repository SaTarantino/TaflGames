#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TaflGamesPiece.generated.h"

UCLASS()
class TAFLGAMES_API ATaflGamesPiece : public AActor
{
	GENERATED_BODY()

	UPROPERTY(Category = Piace, VisibleDefaultsOnly, meta = (AllowPrivateAccess = "ture"))
	class USceneComponent* PieceRoot;

	UPROPERTY(Category = Piace, VisibleDefaultsOnly, meta = (AllowPrivateAccess = "ture"))
	class UStaticMeshComponent* PieceMesh;

public:
	// Sets default values for this actor's properties
	ATaflGamesPiece();

	UPROPERTY()
	class UMaterial* BaseMaterial;

	UPROPERTY()
	class ATaflGamesBlockGrid* OwningGrid;
	//class ATaflGamesBlock* OwningBlock;

	UFUNCTION()
	void PiaceClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);

	void HandleClicked();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	FORCEINLINE class USceneComponent* GetPieceRoot() const { return PieceRoot; }
	FORCEINLINE class UStaticMeshComponent* GetPieceMesh() const { return PieceMesh; }
};
