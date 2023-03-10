#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Collectible.h"
#include "Ghost_Actor.generated.h"


UCLASS()
class PAC_MAN_API AGhost_Actor : public AActor
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere)
		int MissChance;

	UPROPERTY(EditAnywhere)
		float Speed;

	UPROPERTY(EditAnywhere)
		FVector Direction;

	UPROPERTY(VisibleAnywhere) 
		class UStaticMeshComponent* SphereVisual;

private:

	class UMaterialInstanceDynamic * Materialnstance;
	class USphereComponent* SphereComponent;

	bool bCanEat;

	FVector DirectionToChange; 
	FVector StartDirection;
	FVector StartPosition;

	FLinearColor StartingColor;

	FTimerHandle UnusedHandle;
	
public:
	AGhost_Actor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:

	UFUNCTION() 
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

public:

	UFUNCTION()
		void ChangeDirection();
};