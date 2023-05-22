// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "MortarAndPestleActor.generated.h"

UCLASS()
class AMortarAndPestleActor : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMortarAndPestleActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mortar Info")
		UStaticMeshComponent* MortarMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mortar Info")
		UStaticMeshComponent* PestleMeshComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Interact_Implementation(AActor* InteractingActor) override;

	FString GetInteractMessage_Implementation() override;
};
