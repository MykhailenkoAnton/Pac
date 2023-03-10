#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "Path_Trigger.generated.h"

/**
 * 
 */
UCLASS()
class PAC_MAN_API APath_Trigger : public ATriggerBox
{
	GENERATED_BODY()

private:
	FVector Direction;

	int Distance; 
		
	bool Updatable;

public:

	static TArray<FVector> PossibleMoves; 

public:
	UPROPERTY(EditAnywhere)
	class APath_Trigger	*		UpperPathTrigger;

	UPROPERTY(EditAnywhere)
	class APath_Trigger *		RightPathTrigger;

	UPROPERTY(EditAnywhere)
	class APath_Trigger *		InferiorPathTrigger;
	
	UPROPERTY(EditAnywhere)
	class APath_Trigger *		LeftPathTrigger;

public:

	APath_Trigger();

public:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override; 

public:


public:

	FVector GetDirection(int MissChancePercentage);	

	TArray<FVector> GetDirectionsAvailable();

	FVector GetRandomDirectionAvailable();
};