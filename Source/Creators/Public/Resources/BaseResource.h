// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CreatorsBaseActor.h"
#include "BaseResource.generated.h"

UCLASS()
class CREATORS_API ABaseResource : public ACreatorsBaseActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseResource();

public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//////////////////////////////////////////////////////////////////////////
	// reading data

	/** amount of resources left in node */
	UFUNCTION(BlueprintCallable, Category = Resource)
		int32 GetAvailableResources() const;

	/** initial amount of resources */
	int32 GetInitialResources() const;

	/** blueprint event: demolished */
	UFUNCTION(BlueprintCallable, Category = Resource)
		virtual void OnDepleted();

	/** reset resource actor to reuse it again in game (it'll not unhide this actor) */
	UFUNCTION(BlueprintCallable, Category = Resource)
		void ResetResource(bool UnhideInGame = true);

	/** reset resource actor to reuse it again in game (it'll not unhide this actor) */
	UFUNCTION(BlueprintCallable, Category = Resource)
		int32 RetrieveResources(int32 amount);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Number of Resources left
	UPROPERTY(EditDefaultsOnly, Category = Resource)
		int32 CurrentResources;
	
};
