// Fill out your copyright notice in the Description page of Project Settings.

#include "Creators.h"
#include "GroundBuilding.h"

// Sets default values
AGroundBuilding::AGroundBuilding()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh->SetMobility(EComponentMobility::Static);
	Mesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	Mesh->SetCollisionResponseToChannel(COLLISION_FLOOR, ECollisionResponse::ECR_Block);
	Mesh->SetCollisionResponseToChannel(COLLISION_PANCAMERA, ECollisionResponse::ECR_Block);
}
