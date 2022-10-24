
#include "Boid.h"
#include "Kismet/KismetMathLibrary.h"


ABoid::ABoid()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RootComponent = SphereComponent;
	
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(RootComponent);

}


void ABoid::BeginPlay()
{
	Super::BeginPlay();

	auto Animation = SkeletalMesh->AnimationData.AnimToPlay;
	SkeletalMesh->SetPosition(FMath::RandRange(0.0f, Animation->GetPlayLength()));
}

void ABoid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FindNearbyBoids();
	
}

void ABoid::FindNearbyBoids()
{
	TArray<FHitResult> HitResults;
	int Radius = 800;
	int Separate = 150;
	FVector Offset = GetActorForwardVector() * Radius * 0.6;
	FVector Length = FVector(5, 5, 5);
	FVector Start = GetActorLocation() + Offset;
	FVector End = Start + Length;
	FCollisionShape Sphere = FCollisionShape::MakeSphere(Radius);
	FCollisionQueryParams Params = FCollisionQueryParams("Tag", false, this);
	Params.bIgnoreBlocks = true;
	Params.bFindInitialOverlaps = true;
	Params.bIgnoreTouches = false;
	
	GetWorld()->SweepMultiByChannel(HitResults, Start, End,
	   FQuat::Identity, ECC_WorldDynamic, Sphere, Params);
	DrawDebugSphere(GetWorld(), End, Radius, 10, FColor::Blue);
	
	FVector NearbyBoidsAvgLocation = FVector::Zero();
	// double DistanceToCenter = 0;
	FVector CoheseVector = FVector::Zero();
	
	FVector SeparateVector = FVector::Zero();
	double ClosestBoidDistance = 99999;
	FVector ClosestBoidLocation = FVector::Zero();
	bool bNeighborIsTooClose = false;
	
	FVector NearbyBoidsAvgForward = FVector::Zero();
	FVector NearbyBoidsAvgUp = FVector::Zero();
	FVector AlignVector = FVector::Zero();
	
	int NearbyBoidsCount = 0;
	
	for (auto HitResult : HitResults)
	{
		if (ABoid* OtherBoid = Cast<ABoid>(HitResult.GetActor()))
		{
			if (OtherBoid == this)
			{
				continue;
			}
			NearbyBoidsCount++;

			// Alignment
			NearbyBoidsAvgForward += OtherBoid->GetActorForwardVector();
			NearbyBoidsAvgUp += OtherBoid->GetActorUpVector();
			
			// Cohesion
			NearbyBoidsAvgLocation += OtherBoid->GetActorLocation();

			//Separation
			double DistanceToOther = (GetActorLocation() - OtherBoid->GetActorLocation()).Length();
			DistanceToOther = FMath::Abs(DistanceToOther);
			if (DistanceToOther < Separate && DistanceToOther < ClosestBoidDistance)
			{
				ClosestBoidLocation = OtherBoid->GetActorLocation();
				ClosestBoidDistance = DistanceToOther;
				bNeighborIsTooClose = true;
			}
		}
	}

	// FVector Combined;
	
	if (NearbyBoidsCount > 0)
	{
		// Alignment
		NearbyBoidsAvgForward = NearbyBoidsAvgForward / NearbyBoidsCount;
		NearbyBoidsAvgUp = NearbyBoidsAvgUp / NearbyBoidsCount;
		auto NearByboidsRotation = UKismetMathLibrary::MakeRotFromXZ(NearbyBoidsAvgForward, NearbyBoidsAvgUp);
		SetActorRotation(FQuat::Slerp(GetActorRotation().Quaternion(), NearByboidsRotation.Quaternion(),
			0.5 * GetWorld()->GetDeltaSeconds()));

		// Cohesion
		NearbyBoidsAvgLocation = NearbyBoidsAvgLocation / NearbyBoidsCount;
		CoheseVector = NearbyBoidsAvgLocation - GetActorLocation();
		SetActorLocation(FMath::Lerp(GetActorLocation(), NearbyBoidsAvgLocation,
			0.1 * GetWorld()->GetDeltaSeconds()));

		// Separation
		SeparateVector = ClosestBoidLocation - GetActorLocation();
		if (bNeighborIsTooClose)
		{
			DrawDebugLine(GetWorld(), GetActorLocation(), ClosestBoidLocation,
					!bNeighborIsTooClose ? FColor::Green : FColor::Red);
			
			SetActorLocation(FMath::Lerp(GetActorLocation(), GetActorLocation() - SeparateVector,
			0.5 * GetWorld()->GetDeltaSeconds()));
		}
	}

	// Go forward
	AddActorWorldOffset(GetActorForwardVector() * ForwardSpeed * GetWorld()->GetDeltaSeconds());

	// Add random rotation
	AddActorWorldRotation(FRotator(FMath::RandRange(-1, 1),
		FMath::RandRange(-1, 1),
		FMath::RandRange(-1, 1)));

	
	


	

}




