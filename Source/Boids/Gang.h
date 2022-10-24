
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gang.generated.h"

class ABoid;


UCLASS()
class BOIDS_API AGang : public AActor
{
	GENERATED_BODY()

public:
	AGang();

	UPROPERTY()
	TArray<ABoid*> Gang;
	UPROPERTY(BlueprintReadWrite)
	TSubclassOf<ABoid> BoidType;
	UPROPERTY()
	FVector GangDirection;
	UPROPERTY()
	FVector GangCenter;
	UPROPERTY()
	float Alignment = 1;
	UPROPERTY()
	float Cohesion = 1;
	UPROPERTY()
	float Avoidance = 1;
	
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	// FVector GetGangDirection();
	// FVector GetGangCenter();
};
