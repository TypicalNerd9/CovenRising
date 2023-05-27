// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "BrazierActor.generated.h"

UCLASS()
class ABrazierActor : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABrazierActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBoxComponent* BrazierCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* Brazier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UNiagaraComponent* Flame;

	UPROPERTY()
		bool bIsLit;

	UPROPERTY(VisibleAnywhere, BlueprintRead)
		class ARitualActor* RitualActor;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Interact_Implementation(AActor* InteractingActor) override;

	FString GetInteractMessage_Implementation() override;
};
