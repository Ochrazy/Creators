// Fill out your copyright notice in the Description page of Project Settings.

#include "Creators.h"
#include "Forester.h"
#include "ForesterLodge.h"

// Sets default values
AForester::AForester()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
}

// Called when the game starts or when spawned
void AForester::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AForester::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AForester::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

