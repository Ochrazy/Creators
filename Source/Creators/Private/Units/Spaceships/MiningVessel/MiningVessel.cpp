// Fill out your copyright notice in the Description page of Project Settings.

#include "Creators.h"
#include "MiningVessel.h"


// Sets default values
AMiningVessel::AMiningVessel()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

// Called when the game starts or when spawned
void AMiningVessel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMiningVessel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult HitResult;
	AddActorLocalOffset(FVector(0.f, dir * -500.f, 0.f) * DeltaTime, true, &HitResult);

	if (HitResult.bBlockingHit)
	{
		FVector Origin, Extent;
		HitResult.GetActor()->GetActorBounds(true, Origin, Extent);
		float diffZ = Extent.Z - fabsf(HitResult.GetActor()->GetActorLocation().Z - GetActorLocation().Z);
		float diffX = Extent.X - fabsf(HitResult.GetActor()->GetActorLocation().X - GetActorLocation().X);

		if (diffZ < diffX)
		{
			if (HitResult.GetActor()->GetActorLocation().Z > GetActorLocation().Z)
			{
				AddActorLocalOffset(FVector(0.f, 0.f, -500.f) * DeltaTime, true);
			}
			else if (HitResult.GetActor()->GetActorLocation().Z < GetActorLocation().Z)
			{
				AddActorLocalOffset(FVector(0.f, 0.f, 500.f) * DeltaTime, true);
			}
			else
			{
				AddActorLocalOffset(FVector(0.f, 0.f, FMath::FRandRange(-500.f, 500.f)) * DeltaTime, true);
			}
		}
		else 
		{
			if (HitResult.GetActor()->GetActorLocation().X > GetActorLocation().X)
			{
				AddActorLocalOffset(FVector(-500.f, 0.f, 0.f) * DeltaTime, true);
			}
			else if (HitResult.GetActor()->GetActorLocation().X < GetActorLocation().X)
			{
				AddActorLocalOffset(FVector(500.f, 0.f, 0.f) * DeltaTime, true);
			}
			else
			{
				AddActorLocalOffset(FVector(FMath::FRandRange(-500.f, 500.f), 0.f, 0.f) * DeltaTime, true);
			}
		}
	}

}
