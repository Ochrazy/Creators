// Fill out your copyright notice in the Description page of Project Settings.

#include "Creators.h"
#include "CommandCenterWidget.h"
#include "CreatorsBaseWidgetComponent.h"
#include "CollectorBase.h"
#include "GroundBuilding.h"
#include "CreatorsCommandCenter.h"
#include "Block.h"
#include <stdlib.h> 

// Sets default values
ACreatorsCommandCenter::ACreatorsCommandCenter()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	CurrentBuildingMode = BuildingMode::None;

	WidgetComponent = CreateDefaultSubobject<UCreatorsBaseWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetupAttachment(RootComponent);
	WidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 40.0f));
	WidgetComponent->SetVisibility(true);

	RootComponent->SetMobility(EComponentMobility::Static);

	CubeBounds = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeBounds"));
	CubeBounds->SetupAttachment(RootComponent);
	CubeBounds->SetVisibility(true);
	CubeBounds->SetWorldScale3D(FVector(10.1f, 10.1f, 10.1f));
	CubeBounds->SetMobility(EComponentMobility::Movable);
	CubeBounds->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Game/Geometry/Meshes/1M_Cube.1M_Cube'"));
	BlockAsset = MeshAsset.Object;

	for (int i = 0; i < 9; i++)
	{
		UStaticMeshComponent* NewBlock = CreateDefaultSubobject<UStaticMeshComponent>(FName(*("Block" + FString::FromInt(i))));
		NewBlock->SetupAttachment(RootComponent);
		NewBlock->SetStaticMesh(BlockAsset);
		NewBlock->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		NewBlock->SetCollisionResponseToChannel(COLLISION_FLOOR, ECollisionResponse::ECR_Block);
		NewBlock->SetCollisionResponseToChannel(COLLISION_PANCAMERA, ECollisionResponse::ECR_Block);
		Blocks.Add(NewBlock);
	}
}

void ACreatorsCommandCenter::OnConstruction(const FTransform& Transform)
{
	Super::PostInitializeComponents();

	for (int i = 0; i < 9; i++)
	{
		Blocks[i]->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		Blocks[i]->SetCollisionResponseToChannel(COLLISION_FLOOR, ECollisionResponse::ECR_Block);
		Blocks[i]->SetCollisionResponseToChannel(COLLISION_PANCAMERA, ECollisionResponse::ECR_Block);
		Blocks[i]->SetWorldScale3D(FVector(5.01f, 5.01f, 5.01f));
	}

	// 0.01f so that Blocks overlap slightly -> Navigation works this way!
	const FVector BoxExtends = Blocks[0]->Bounds.BoxExtent * 2.f - 0.01f;
	const float LocationUnderCenter = -(BoxExtends.Z*0.5f) - Mesh->Bounds.BoxExtent.Z;

	Blocks[0]->SetRelativeLocation(FVector(0.f, 0.f, LocationUnderCenter));
	Blocks[1]->SetRelativeLocation(FVector(BoxExtends.X, 0.f, LocationUnderCenter));
	Blocks[2]->SetRelativeLocation(FVector(-BoxExtends.X, 0.f, LocationUnderCenter));
	Blocks[3]->SetRelativeLocation(FVector(0.f, BoxExtends.Y, LocationUnderCenter));
	Blocks[4]->SetRelativeLocation(FVector(0.f, -BoxExtends.Y, LocationUnderCenter));
	Blocks[5]->SetRelativeLocation(FVector(BoxExtends.X, BoxExtends.Y, LocationUnderCenter));
	Blocks[6]->SetRelativeLocation(FVector(-BoxExtends.X, BoxExtends.Y, LocationUnderCenter));
	Blocks[7]->SetRelativeLocation(FVector(BoxExtends.X, -BoxExtends.Y, LocationUnderCenter));
	Blocks[8]->SetRelativeLocation(FVector(-BoxExtends.X, -BoxExtends.Y, LocationUnderCenter));

	const FVector ScaleBounds = FVector(5.01f, 5.01f, 5.01f) * 3.f;
	CubeBounds->SetWorldScale3D(ScaleBounds + 0.1f);

}
// Called when the game starts or when spawned
void ACreatorsCommandCenter::BeginPlay()
{
	Super::BeginPlay();

	// Add Delegates
	UCommandCenterWidget* ccWidget = Cast<UCommandCenterWidget>(WidgetComponent->GetUserWidgetObject());
	if (ccWidget)
	{
		ccWidget->CollectorBaseButton->OnClicked.AddDynamic(this, &ACreatorsCommandCenter::BuildingModeCollector);
		ccWidget->ForesterLodgeButton->OnClicked.AddDynamic(this, &ACreatorsCommandCenter::BuildingModeForester);
		ccWidget->BlockButton->OnClicked.AddDynamic(this, &ACreatorsCommandCenter::BuildingModeBlock);
	}
}

void ACreatorsCommandCenter::NormalBuildingModeTick()
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

	FVector origin, extent;
	BuildingToPlace->GetActorBounds(true, origin, extent);

	if (HitResult.bBlockingHit == false)
	{
		BuildingToPlace->SetActorLocation(WorldOrigin + WorldDirection * 7000);
		BuildingToPlace->DynMaterial->SetVectorParameterValue("Overlay", FLinearColor(1.f, 0.f, 0.f, 0.5f));
	}
	else
	{
		BuildingToPlace->SetActorLocation(HitResult.Location + FVector(0.f, 0.f, extent.Z + 10.f));

		// Check if Building to Place overlaps
		TArray<AActor*> overlappingActors;
		BuildingToPlace->GetOverlappingActors(overlappingActors);
		UStaticMeshComponent* GroundBox = Cast<UStaticMeshComponent>(HitResult.GetComponent());
		// AABB only -> no rotation supported!
		if (overlappingActors.Num() > 0 /*|| !GroundBox*/ || !CubeBounds->Bounds.GetBox().IsInside(FBox(origin - extent, origin + extent)))
		{
			BuildingToPlace->DynMaterial->SetVectorParameterValue("Overlay", FLinearColor(1.f, 0.f, 0.f, 0.5f));
		}
		else
		{
			BuildingToPlace->DynMaterial->SetVectorParameterValue("Overlay", FLinearColor(1.f, 0.f, 0.f, 0.f));

			if (GetWorld()->GetFirstPlayerController()->WasInputKeyJustPressed(EKeys::LeftMouseButton))
			{
				LeaveBuildingMode();
			}
		}
	}
}
void ACreatorsCommandCenter::BlockBuildingModeTick()
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
				FPlane plane(GetActorLocation() - FVector(0.f, 0.f, Mesh->Bounds.BoxExtent.Z), FVector(0.f, 0.f, 1.f));
				WorldOrigin = FMath::LinePlaneIntersection(WorldOrigin, WorldOrigin + WorldDirection * 10000, plane);
			}
		}
	}

	BuildingToPlace->SetActorLocation(WorldOrigin - FVector(0.f, 0.f, Blocks[0]->Bounds.BoxExtent.Z * 0.75f));

	FVector ToPlaceBlockLoc = BuildingToPlace->GetActorLocation();
	float minDist = 1000.f * 1000.f;
	int minIndex = 0;
	for (int idx = 0; idx < Blocks.Num(); idx++)
	{
		float currentDist = FVector::DistSquared2D(Blocks[idx]->GetComponentLocation(), ToPlaceBlockLoc);
		if (minDist > currentDist)
		{
			minDist = currentDist;
			minIndex = idx;
		}
	}

	UStaticMeshComponent* OtherBlock = Blocks[minIndex];
	FVector OtherBlockLoc = OtherBlock->GetComponentLocation();

	float BlocksDiffX = ToPlaceBlockLoc.X - OtherBlockLoc.X;
	float BlocksDiffY = ToPlaceBlockLoc.Y - OtherBlockLoc.Y;

	FVector origin = OtherBlock->Bounds.Origin, extent = OtherBlock->Bounds.BoxExtent;

	// Snap the Location of the Box to the nearest Box
	if (std::abs(BlocksDiffX) >= std::abs(BlocksDiffY))
	{
		if (BlocksDiffX >= 0)
			BuildingToPlace->SetActorLocation(origin + FVector(extent.X * 2.0f - 0.01f, 0.f, 0.f));
		else BuildingToPlace->SetActorLocation(origin + FVector(-extent.X * 2.0f - 0.01f, 0.f, 0.f));
	}
	else if (BlocksDiffY >= 0)
		BuildingToPlace->SetActorLocation(origin + FVector(0.f, extent.Y * 2.0f - 0.01f, 0.f));
	else
	{
		BuildingToPlace->SetActorLocation(origin + FVector(0.f, -extent.Y * 2.0f - 0.01f, 0.f));
	}


	// Check if current Position is already occupied by another box
	bool bLeaveBuildingMode = true;
	FVector ToPlaceLocation = BuildingToPlace->GetActorLocation();
	for (int idxOcc = 0; idxOcc < Blocks.Num(); idxOcc++)
	{
		if (FVector::DistSquared2D(Blocks[idxOcc]->GetComponentLocation(), ToPlaceLocation) < extent.X) bLeaveBuildingMode = false;
	}

	if (bLeaveBuildingMode)
	{
		if (GetWorld()->GetFirstPlayerController()->WasInputKeyJustPressed(EKeys::LeftMouseButton))
		{
			const FVector ScaleBounds = CubeBounds->GetComponentScale();

			if (ToPlaceLocation.X > CubeBounds->Bounds.GetBox().Max.X)
			{
				CubeBounds->SetWorldScale3D(ScaleBounds + FVector(5.11f, 0.f, 0.f));
				CubeBounds->AddRelativeLocation(FVector(extent.X, 0.f, 0.f));
			}
			else if (ToPlaceLocation.Y > CubeBounds->Bounds.GetBox().Max.Y)
			{
				CubeBounds->SetWorldScale3D(ScaleBounds + FVector(0.f, 5.11f, 0.f));
				CubeBounds->AddRelativeLocation(FVector(0.f, extent.Y, 0.f));
			}
			else if (ToPlaceLocation.X < CubeBounds->Bounds.GetBox().Min.X)
			{
				CubeBounds->SetWorldScale3D(ScaleBounds + FVector(5.11f, 0.f, 0.f));
				CubeBounds->AddRelativeLocation(FVector(-extent.X, 0.f, 0.f));
			}
			else if (ToPlaceLocation.Y < CubeBounds->Bounds.GetBox().Min.Y)
			{
				CubeBounds->SetWorldScale3D(ScaleBounds + FVector(0.f, 5.11f, 0.f));
				CubeBounds->AddRelativeLocation(FVector(0.f, -extent.Y, 0.f));
			}

			LeaveBuildingMode();
		}
	}
	else
	{
		BuildingToPlace->SetActorLocation(WorldOrigin - FVector(0.f, 0.f, Blocks[0]->Bounds.BoxExtent.Z * 0.75f));
	}
}

void ACreatorsCommandCenter::Tick(float DeltaTime)
{
	if (CurrentBuildingMode == BuildingMode::Normal)
	{
		NormalBuildingModeTick();
	}
	else if (CurrentBuildingMode == BuildingMode::Block)
	{
		BlockBuildingModeTick();
	}
}

void ACreatorsCommandCenter::LeaveBuildingMode()
{
	if (CurrentBuildingMode == BuildingMode::Normal)
	{
		CurrentBuildingMode = BuildingMode::None;
		BuildingToPlace->SetActorEnableCollision(true);
		Cast<UPrimitiveComponent>(BuildingToPlace->GetRootComponent())->bGenerateOverlapEvents = true;
		Cast<UPrimitiveComponent>(BuildingToPlace->GetRootComponent())->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		Cast<UPrimitiveComponent>(BuildingToPlace->GetRootComponent())->SetCollisionProfileName(FName("BlockAllDynamic"));
		BuildingToPlace.Reset();
	}
	else if (CurrentBuildingMode == BuildingMode::Block)
	{
		CurrentBuildingMode = BuildingMode::None;

		// Create New Block and use this instead of Block Actor
		UStaticMeshComponent* NewBlock = NewObject<UStaticMeshComponent>(this, FName(*("Block" + FString::FromInt(Blocks.Num()))));
		NewBlock->SetupAttachment(RootComponent);
		NewBlock->SetStaticMesh(BlockAsset);
		NewBlock->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		NewBlock->SetCollisionResponseToChannel(COLLISION_FLOOR, ECollisionResponse::ECR_Block);
		NewBlock->SetCollisionResponseToChannel(COLLISION_PANCAMERA, ECollisionResponse::ECR_Block);
		NewBlock->SetWorldScale3D(FVector(5.01f, 5.01f, 5.01f));
		NewBlock->SetWorldLocation(BuildingToPlace->GetActorLocation());
		NewBlock->RegisterComponent();
		Blocks.Add(NewBlock);

		// Destroy Proxy Block Actor
		BuildingToPlace->Destroy();
		BuildingToPlace.Reset();
	}
}

void ACreatorsCommandCenter::EnterBuildingMode(TSubclassOf<ABuilding> buildingClass)
{
	const FTransform transf = FTransform(FVector(0.0, 0.0, -9000.0));
	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	BuildingToPlace = GetWorld()->SpawnActor<ABuilding>(buildingClass, FVector(0.0, 0.0, -9000.0), FRotator(0.0), params);
	if (BuildingToPlace.IsValid())
	{
		BuildingToPlace->SetActorEnableCollision(true);
		Cast<UPrimitiveComponent>(BuildingToPlace->GetRootComponent())->bGenerateOverlapEvents = true;
		Cast<UPrimitiveComponent>(BuildingToPlace->GetRootComponent())->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		Cast<UPrimitiveComponent>(BuildingToPlace->GetRootComponent())->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		Cast<UPrimitiveComponent>(BuildingToPlace->GetRootComponent())->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);
	}
}

void ACreatorsCommandCenter::BuildingModeCollector()
{
	CurrentBuildingMode = BuildingMode::Normal;
	EnterBuildingMode(CollectorClass);
}

void ACreatorsCommandCenter::BuildingModeForester()
{
	CurrentBuildingMode = BuildingMode::Normal;
	EnterBuildingMode(ForesterClass);
}

void ACreatorsCommandCenter::BuildingModeBlock()
{
	CurrentBuildingMode = BuildingMode::Block;
	EnterBuildingMode(BlockClass);
}