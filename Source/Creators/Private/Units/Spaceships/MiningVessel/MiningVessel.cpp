// Fill out your copyright notice in the Description page of Project Settings.

#include "Creators.h"
#include "MiningVessel.h"

/* AI Specific includes */
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"


// Sets default values
AMiningVessel::AMiningVessel()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

	m_Target = nullptr;
	m_CurrentAvoidanceVector = FVector(0.f, 0.f, 0.f);
}

// Called when the game starts or when spawned
void AMiningVessel::BeginPlay()
{
	Super::BeginPlay();
	
	if (BehaviorTree->BlackboardAsset)
	{
		BlackboardComp->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	}

	BehaviorComp->StartTree(*BehaviorTree);
}

void AMiningVessel::SetTarget(AActor* target)
{
	m_Target = target;
}

// Called every frame
void AMiningVessel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_Target)
	{
		if (FVector::Distance(GetActorLocation(), m_Target->GetActorLocation()) > (GetSimpleCollisionRadius() + m_Target->GetSimpleCollisionRadius() + 50))
		{
			FHitResult HitResult;
			FVector FlyToDirection = m_Target->GetActorLocation() - GetActorLocation();
			FlyToDirection.Normalize();
			AddActorWorldOffset(500 * FlyToDirection * DeltaTime, true, &HitResult);
			//AddActorLocalOffset(FVector(0, -dir * 500 * DeltaTime, 0), true, &HitResult);

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
						m_CurrentAvoidanceVector = FVector(0.f, 0.f, -500.f);
						AddActorLocalOffset(m_CurrentAvoidanceVector * DeltaTime, true);
					}
					else if (HitResult.GetActor()->GetActorLocation().Z < GetActorLocation().Z)
					{
						m_CurrentAvoidanceVector = FVector(0.f, 0.f, 500.f);
						AddActorLocalOffset(FVector(0.f, 0.f, 500.f) * DeltaTime, true);
					}
					else
					{
						m_CurrentAvoidanceVector = FVector(0.f, 0.f, FMath::FRandRange(-500.f, 500.f));
						AddActorLocalOffset(m_CurrentAvoidanceVector * DeltaTime, true);
					}
				}
				else
				{
					FHitResult HitResult2;
					if (m_CurrentAvoidanceVector.X == 0.f || HitResult.GetActor()->IsRootComponentMovable())
					{
						if (HitResult.GetActor()->GetActorLocation().X > GetActorLocation().X)
						{
							m_CurrentAvoidanceVector = FVector(-500.f, 0.f, 0.f);
							AddActorLocalOffset(FVector(-500.f, 0.f, 0.f) * DeltaTime, true, &HitResult2);
						}
						else if (HitResult.GetActor()->GetActorLocation().X < GetActorLocation().X)
						{
							m_CurrentAvoidanceVector = FVector(500.f, 0.f, 0.f);
							AddActorLocalOffset(FVector(500.f, 0.f, 0.f) * DeltaTime, true, &HitResult2);
						}
						else
						{
							m_CurrentAvoidanceVector = FVector(FMath::FRandRange(-500.f, 500.f), 0.f, 0.f);
							AddActorLocalOffset(m_CurrentAvoidanceVector * DeltaTime, true, &HitResult2);
						}
					}
					else
						AddActorLocalOffset(m_CurrentAvoidanceVector * DeltaTime, true, &HitResult2);

					// Try Up/Down
					if (HitResult2.bBlockingHit)
					{
						if (HitResult.GetActor()->GetActorLocation().Z > GetActorLocation().Z)
						{
							m_CurrentAvoidanceVector = FVector(0.f, 0.f, -500.f);
							AddActorLocalOffset(m_CurrentAvoidanceVector * DeltaTime, true);
						}
						else if (HitResult.GetActor()->GetActorLocation().Z < GetActorLocation().Z)
						{
							m_CurrentAvoidanceVector = FVector(0.f, 0.f, 500.f);
							AddActorLocalOffset(FVector(0.f, 0.f, 500.f) * DeltaTime, true);
						}
						else
						{
							m_CurrentAvoidanceVector = FVector(0.f, 0.f, FMath::FRandRange(-500.f, 500.f));
							AddActorLocalOffset(m_CurrentAvoidanceVector * DeltaTime, true);
						}
					}
				}
			}
			else
			{
				m_CurrentAvoidanceVector = FVector(0.f, 0.f, 0.f);
			}
		}
	}
}

