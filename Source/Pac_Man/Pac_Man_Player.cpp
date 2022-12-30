#include "Pac_Man_Player.h"
#include "Pac_ManGameModeBase.h"
#include "Components/InputComponent.h"
#include "Components/SphereComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Pac_Man_MovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Path_Trigger.h"
#include "Ghost_Actor.h"
#include "Collectible.h"
#include "Materials/MaterialInstanceDynamic.h"

APac_Man_Player::APac_Man_Player()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = SphereComponent;
	SphereComponent->InitSphereRadius(40.0f);
	SphereComponent->SetCollisionProfileName(TEXT("Pawn"));

	SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	SphereVisual->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Engine/BasicShapes/Sphere.Sphere"));

	if (SphereVisualAsset.Succeeded())
	{
		SphereVisual->SetStaticMesh(SphereVisualAsset.Object);
		SphereVisual->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
		SphereVisual->SetWorldScale3D(FVector(0.8f));
	}

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	MovementComponent = CreateDefaultSubobject<UPac_Man_MovementComponent>(TEXT("CustomMovementComponent"));
	MovementComponent->UpdatedComponent = RootComponent;

	Score = 0;
}

void APac_Man_Player::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &APac_Man_Player::OnBeginOverlap);

	UMaterialInterface *  Material = SphereVisual->GetMaterial(0);
	Materialnstance = UMaterialInstanceDynamic::Create(Material, SphereVisual);
	StartingColor = Materialnstance->K2_GetVectorParameterValue(TEXT("BaseColor"));
	SphereVisual->SetMaterial(0,Materialnstance);
}

void APac_Man_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MovementComponent && (MovementComponent->UpdatedComponent == RootComponent))
	{
		MovementComponent->AddInputVector(Direction*Speed);
	}
}

void APac_Man_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APac_Man_Player::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APac_Man_Player::MoveRight);
}

void APac_Man_Player::MoveForward(float AxisValue)
{
	if (AxisValue != 0.0f)
	{
		Direction = GetActorForwardVector() * AxisValue;
	}
}

void APac_Man_Player::MoveRight(float AxisValue)
{
	if (AxisValue != 0.0f)
	{
		Direction = GetActorRightVector() * AxisValue;
	}
}

void APac_Man_Player::OnBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ACollectible* Collectible = Cast<ACollectible>(OtherActor);

	if (Collectible)
	{
		
		if (Collectible->Type == ECollectibleTypeEnum::CTE_Coin)
		{
			++Score;
		}
		else if (Collectible->Type == ECollectibleTypeEnum::CTE_CornerPowerUp)
		{
			//some logic
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Corner"));
		}
		else if(Collectible->Type == ECollectibleTypeEnum::CTE_HunterPowerUp)
		{
			//some logic
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hunter"));
		}
		Collectible->Destroy();
	}
}


FVector APac_Man_Player::GetMovementDirection()
{
	return Direction;
}

UPawnMovementComponent * APac_Man_Player::GetMovementComponent() const
{
	return MovementComponent;
}
