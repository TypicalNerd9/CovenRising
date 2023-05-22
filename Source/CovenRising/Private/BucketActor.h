// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "Components/TimelineComponent.h"
#include "NiagaraComponent.h"
#include "BucketActor.generated.h"

UCLASS()
class ABucketActor : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABucketActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bucket Info")
		class UStaticMeshComponent* BucketMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bucket Info")
		class UStaticMeshComponent* WaterMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bucket Info")
		class UStaticMeshComponent* CleaningMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bucket Info")
		UTimelineComponent* CleaningTimelineComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bucket Info")
		UNiagaraComponent* CleaningDirtParticles;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Tank)
		class UTankActorComponent* TankComponent;

	UPROPERTY()
		bool bIsCleaning;

	FTimerHandle CleaningTimer;
	FTimerHandle StartCleaningTimer;

	UFUNCTION()
		void AnimationEnded(ACovenRisingCharacter* Character);

	UFUNCTION()
		void AnimationStarted(ACovenRisingCharacter* Character);

	//FOnTimelineEvent TimelineFinishedEvent;

	//UFUNCTION()
		//void TimelineFinishedFunction();

	FOnTimelineFloat UpdateCleaningTrack;

	UFUNCTION()
		void UpdateCleaningMeshLocation(float TimelineOutput);
public:	
	UPROPERTY(EditAnywhere)
		UCurveFloat* CleaningTimelineCurve;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Interact_Implementation(AActor* InteractingActor) override;

	FString GetInteractMessage_Implementation() override;

};
