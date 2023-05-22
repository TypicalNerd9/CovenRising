// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "Components/TimelineComponent.h"
#include "DoorActor.generated.h"

UCLASS()
class ADoorActor : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoorActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door Details")
		class UStaticMeshComponent* DoorMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door Details")
		UTimelineComponent* DoorTimelineComp;

	FOnTimelineFloat UpdateDoorTrack;

	UPROPERTY()
		bool bIsOpen;

	UPROPERTY()
		int FacingDirection;

	UPROPERTY()
		FRotator OriginalDoorRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCurveFloat* DoorTimelineCurve;

	UFUNCTION()
		void UpdateDoorRotation(float TimelineOutput);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Interact_Implementation(AActor* InteractingActor) override;

	FString GetInteractMessage_Implementation() override;
};
