#include "Path_Trigger.h"
#include "Components/BoxComponent.h"
#include "Engine/GameEngine.h"

TArray<FVector> APath_Trigger::PossibleMoves;

APath_Trigger::APath_Trigger()
{
	PrimaryActorTick.bCanEverTick = true;

	if (PossibleMoves.Num() == 0)
	{
		PossibleMoves = { GetActorForwardVector(), GetActorRightVector(), -GetActorForwardVector(), -GetActorRightVector() };
	}
}

void APath_Trigger::BeginPlay()
{
	Super::BeginPlay();
}

void APath_Trigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Updatable = true;
}

FVector APath_Trigger::GetDirection(int MissChancePercentage)
{
	if (FMath::RandRange(0, 100) < MissChancePercentage)
	{
		return GetRandomDirectionAvailable();
	}
	else 
	{
		if(Direction != FVector(0.f, 0.f, 0.f))
			return Direction;

		else return GetRandomDirectionAvailable();
	}
}

TArray<FVector> APath_Trigger::GetDirectionsAvailable()
{
	TArray<FVector> DirectionsAvailable = {};

	if (UpperPathTrigger)
		DirectionsAvailable.Add(PossibleMoves[0]);

	if (RightPathTrigger)
		DirectionsAvailable.Add(PossibleMoves[1]);

	if (InferiorPathTrigger)
		DirectionsAvailable.Add(PossibleMoves[2]);

	if (LeftPathTrigger)
		DirectionsAvailable.Add(PossibleMoves[3]);

	return DirectionsAvailable;
}

FVector APath_Trigger::GetRandomDirectionAvailable()
{
	TArray<FVector> TempDirections = GetDirectionsAvailable();

	if (TempDirections.Num() > 0)
	{
		return TempDirections[FMath::RandRange(0, TempDirections.Num() - 1)]; 
	}

	return FVector(0.f);
}
