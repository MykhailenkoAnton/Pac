#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Pac_Man_Player.generated.h"

UCLASS()
class PAC_MAN_API APac_Man_Player : public APawn
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere)
		float Speed;

	UPROPERTY(VisibleAnywhere) 
		UStaticMeshComponent* SphereVisual;


private:

	class USphereComponent* SphereComponent;

	class UPac_Man_MovementComponent* MovementComponent;

	class UMaterialInstanceDynamic * Materialnstance;

	FVector Direction;
	FLinearColor StartingColor; 

protected:

	UPROPERTY(BlueprintReadOnly)
		int Score;

public:
	APac_Man_Player();

protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	void MoveForward(float AxisValue);

	void MoveRight(float AxisValue);

private:

	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


public:

	FVector GetMovementDirection();

	virtual UPawnMovementComponent* GetMovementComponent() const override;
};