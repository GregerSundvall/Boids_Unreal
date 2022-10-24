

#include "Gang.h"
#include "Boid.h"


AGang::AGang()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGang::BeginPlay()
{
	Super::BeginPlay();

	// ABoid* Boid = GetWorld()->SpawnActor<ABoid>();
	// Boid->Gang = this;
	// Boid->GangID = Gang.Num();
	// Gang.Add(Boid);
}

void AGang::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// GangDirection = GetGangDirection();
	// GangCenter = GetGangCenter();
}

// FVector AGang::GetGangDirection()
// {
// 	FVector Sum;
// 	for (ABoid Boid : Gang)
// 	{
// 		Sum += Boid.GetActorForwardVector();
// 	}
// 	return Sum / Gang.Num();
// }
//
// FVector AGang::GetGangCenter()
// {
// 	FVector Sum;
// 	for (ABoid Boid : Gang)
// 	{
// 		Sum += Boid.GetActorLocation();
// 	}
// 	return Sum / Gang.Num();
// }

