
#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "Boid.generated.h"

// class AGang;

UCLASS()
class BOIDS_API ABoid : public AActor
{
	GENERATED_BODY()

public:
	ABoid();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USphereComponent* SphereComponent;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USkeletalMeshComponent* SkeletalMesh;
	
	UPROPERTY(BlueprintReadWrite)
	double BoidSize = 20;
	UPROPERTY()
	double ForwardSpeed = 100;
	UPROPERTY()
	double AvoidDistance = 10;
	UPROPERTY()
	float AlignmentWeight = 1;
	UPROPERTY()
	float CohesionWeight = 1;
	UPROPERTY()
	float SeparationWeight = 1;
	
	// FVector NearbyBoidsAvgForward;
	// FVector NearbyBoidsAvgLocation;
	// UPROPERTY()
	// float NeighborhoodRadius = 3;
	// UPROPERTY()
	// TArray<ABoid*> Neighbors;
	// UPROPERTY()
	// TArray<ABoid*> Intrusives;
	// UPROPERTY()
	// FVector NeighborhoodCenter;
	// UPROPERTY()
	// FVector NeighborhoodDirection;
	// UPROPERTY()
	// double NeighborhoodRotX;
	// UPROPERTY()
	// double NeighborhoodRotY;
	// UPROPERTY()
	// double NeighborhoodRotZ;
	// UPROPERTY()
	// FVector LocationDiff;
	// UPROPERTY()
	// float DirectionDiff;
	// UPROPERTY()
	// TArray<ABoid*> NearbyBoids;
	// UPROPERTY()
	// FRotator NearbyBoidsAvgRotation;
	// UPROPERTY()
	// FVector NearbyBoidsRight;
	// UPROPERTY()
	// FVector NearbyBoidsUp;
	// UPROPERTY()
	// FVector CombinedForward;
	// UPROPERTY()
	// FVector CombinedRight;
	// UPROPERTY()
	// FVector CombinedUp;
	
	// UPROPERTY()
	// AGang* Gang;
	// UPROPERTY()
	// int GangID;

protected:
	virtual void BeginPlay() override;
	void FindNearbyBoids();
	void Align();
	void GoTowardsCenter();

public:
	virtual void Tick(float DeltaTime) override;
};
