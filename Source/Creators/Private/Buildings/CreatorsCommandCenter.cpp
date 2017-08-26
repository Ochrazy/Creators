// Fill out your copyright notice in the Description page of Project Settings.

#include "Creators.h"
#include "CommandCenterWidget.h"
#include "CreatorsBaseWidgetComponent.h"
#include "CollectorBase.h"
#include "GroundBuilding.h"
#include "CreatorsCommandCenter.h"

// Sets default values
ACreatorsCommandCenter::ACreatorsCommandCenter()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	bBuildingMode = false;

	WidgetComponent = CreateDefaultSubobject<UCreatorsBaseWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetupAttachment(RootComponent);
	WidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 40.0f));
	WidgetComponent->SetVisibility(true);

	SetCubeNumber(GetUniqueID());
}

// Called when the game starts or when spawned
void ACreatorsCommandCenter::BeginPlay()
{
	Super::BeginPlay();

	// Add Delegates
	UCommandCenterWidget* ccWidget = Cast<UCommandCenterWidget>(WidgetComponent->GetUserWidgetObject());
	if (ccWidget)
		ccWidget->CollectorBaseButton->OnClicked.AddDynamic(this, &ACreatorsCommandCenter::EnterBuildingMode);
}

void ACreatorsCommandCenter::Tick(float DeltaTime)
{
	if (bBuildingMode)
	{
		FHitResult HitResult;
		ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(GetWorld()->GetFirstLocalPlayerFromController());
		FVector WorldOrigin;
		FVector WorldDirection;
		if (LocalPlayer && LocalPlayer->ViewportClient)
		{
			FVector2D MousePosition;
			if (LocalPlayer->ViewportClient->GetMousePosition(MousePosition))
			{
				if (UGameplayStatics::DeprojectScreenToWorld(GetWorld()->GetFirstPlayerController(), MousePosition, WorldOrigin, WorldDirection) == true)
				{
					GetWorld()->LineTraceSingleByChannel(HitResult, WorldOrigin, WorldOrigin + WorldDirection * 10000, COLLISION_FLOOR);
				}
			}
		}

		if (HitResult.bBlockingHit == false)
		{
			FVector origin, extent;
			BuildingToPlace->GetActorBounds(true, origin, extent);
			BuildingToPlace->SetActorLocation(WorldOrigin + WorldDirection * 7000);
			BuildingToPlace->DynMaterial->SetVectorParameterValue("Overlay", FLinearColor(1.f, 0.f, 0.f, 0.5f));
		}
		else 
		{
			FVector origin, extent;
			BuildingToPlace->GetActorBounds(true, origin, extent);
			BuildingToPlace->SetActorLocation(HitResult.Location + FVector(0.f, 0.f, extent.Z));

			// Check if Building to Place overlaps
			TArray<AActor*> overlappingActors;
			BuildingToPlace->GetOverlappingActors(overlappingActors);
			AGroundBuilding* Ground = Cast<AGroundBuilding>(HitResult.GetActor());
			if (overlappingActors.Num() > 0 || !Ground || Ground->GetCubeNumber() != GetCubeNumber())
			{
				BuildingToPlace->DynMaterial->SetVectorParameterValue("Overlay", FLinearColor(1.f, 0.f, 0.f, 0.5f));
			}
			else
			{
				BuildingToPlace->DynMaterial->SetVectorParameterValue("Overlay", FLinearColor(1.f, 0.f, 0.f, 0.f));

				if (GetWorld()->GetFirstPlayerController()->WasInputKeyJustPressed(EKeys::LeftMouseButton))
				{
					bBuildingMode = false;
					BuildingToPlace->SetActorEnableCollision(true);
					BuildingToPlace->GetRootPrimitiveComponent()->bGenerateOverlapEvents = true;
					BuildingToPlace->GetRootPrimitiveComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
					BuildingToPlace->GetRootPrimitiveComponent()->SetCollisionProfileName(FName("BlockAllDynamic"));
				}
			}
		}
	}
}

void ACreatorsCommandCenter::EnterBuildingMode()
{
	const FTransform transf = FTransform(FVector(0.0, 0.0, -9000.0));
	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	BuildingToPlace = GetWorld()->SpawnActor<ABuilding>(BuildingToPlaceClass, FVector(0.0, 0.0, -9000.0), FRotator(0.0), params);
	if (BuildingToPlace.IsValid())
	{
		BuildingToPlace->SetCubeNumber(GetCubeNumber());
		bBuildingMode = true;
		BuildingToPlace->SetActorEnableCollision(true);
		BuildingToPlace->GetRootPrimitiveComponent()->bGenerateOverlapEvents = true;
		BuildingToPlace->GetRootPrimitiveComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		BuildingToPlace->GetRootPrimitiveComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		BuildingToPlace->GetRootPrimitiveComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);
	}
}