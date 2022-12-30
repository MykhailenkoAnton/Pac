#include "Collectible.h"
#include "Components/StaticMeshComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

ACollectible::ACollectible()
{
	SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	SphereVisual->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Engine/BasicShapes/Sphere.Sphere"));

	if (SphereVisualAsset.Succeeded())
	{
		SphereVisual->SetStaticMesh(SphereVisualAsset.Object);
		SphereVisual->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
		SphereVisual->SetWorldScale3D(FVector(1));
	}
}

void ACollectible::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACollectible::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

