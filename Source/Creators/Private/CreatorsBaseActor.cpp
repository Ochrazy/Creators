// Fill out your copyright notice in the Description page of Project Settings.

#include "Creators.h"
#include "CreatorsBaseActor.h"


// Sets default values
ACreatorsBaseActor::ACreatorsBaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void ACreatorsBaseActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACreatorsBaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

