#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Collectible.generated.h"

UENUM(BlueprintType)		
enum class ECollectibleTypeEnum : uint8
{
	CTE_Coin			UMETA(DisplayName = "Coin"),
	CTE_CornerPowerUp			UMETA(DisplayName = "CornerPowerUp"),
	CTE_HunterPowerUp			UMETA(DisplayName = "HunterPowerUp"),
};

UCLASS()
class PAC_MAN_API ACollectible : public AActor
{
	GENERATED_BODY()
	
public: 

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent * SphereVisual;

	UPROPERTY(EditAnywhere)
		ECollectibleTypeEnum Type;

public:	
	ACollectible();

protected:

	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
};
