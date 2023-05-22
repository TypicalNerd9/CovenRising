// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <CovenRising/Private/ItemData.h>
#include "InteractableInterface.h"
#include "PlantActor.generated.h"

UCLASS()
class APlantActor : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlantActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Plant Info")
	class UStaticMeshComponent* PlantMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Plant Info")
		class UCapsuleComponent* CollisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Plant Info")
	FName ItemDropId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Plant Info")
	int ItemDropCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Plant Info")
	FName SeedDropId;

	bool bIsHarvested, bHasAnimationStarted;

	FVector HarvestDirectionVec;

	FTimerHandle HarvestTimer;

	UFUNCTION()
		void AnimationEnded();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Interact_Implementation(AActor* InteractingActor) override;

	FString GetInteractMessage_Implementation() override;
};
