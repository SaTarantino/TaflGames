#include "TaflGamesPiece.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"

// Sets default values
ATaflGamesPiece::ATaflGamesPiece()
{
	//Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = false;

	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> Shape_Cylinder;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> M_Wood_Oak;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> BaseMaterial;
		FConstructorStatics()
			: Shape_Cylinder(TEXT("/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder"))
			, M_Wood_Oak(TEXT("/Game/StarterContent/Materials/M_Wood_Oak.M_Wood_Oak"))
			, BaseMaterial(TEXT("/Game/Puzzle/Meshes/BaseMaterial.BaseMaterial"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	PieceRoot = CreateDefaultSubobject<USceneComponent>(TEXT("PieceRoot0"));
	RootComponent = PieceRoot;

	PieceMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PiaceMesh0"));
	PieceMesh->SetStaticMesh(ConstructorStatics.Shape_Cylinder.Get());
	PieceMesh->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));
	PieceMesh->SetRelativeLocation(FVector(0.f, 0.f, 25.f));
	PieceMesh->SetMaterial(0, ConstructorStatics.M_Wood_Oak.Get());
	PieceMesh->SetupAttachment(PieceRoot);
	PieceMesh->OnClicked.AddDynamic(this, &ATaflGamesPiece::PiaceClicked);

	// Save a pointer to the orange material.
	M_Wood_Oak = ConstructorStatics.M_Wood_Oak.Get();
	BaseMaterial = ConstructorStatics.BaseMaterial.Get();
}

void ATaflGamesPiece::PiaceClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{
	HandleClicked();
}

void ATaflGamesPiece::HandleClicked()
{
	if (!bIsActive)
	{
		bIsActive = true;
	}
}

void ATaflGamesPiece::Highlight(bool isActive)
{
	if (bIsActive)
	{
		return;
	}

	if (isActive)
	{
		PieceMesh->SetMaterial(0, BaseMaterial);
	}
	else
	{
		PieceMesh->SetMaterial(0, M_Wood_Oak);
	}
}
