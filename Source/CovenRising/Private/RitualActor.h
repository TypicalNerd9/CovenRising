// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include <CovenRising/CovenRisingCharacter.h>
#include "RitualActor.generated.h"

UCLASS()
class ARitualActor : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARitualActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UDecalComponent* RitualCircleDecal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* RitualAltar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* Brazier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBoxComponent* RitualCollision;

	UPROPERTY()
		UMaterialInterface* RitualAltarMaterial;

	UPROPERTY()
		UMaterialInstanceDynamic* RitualAltarMaterialDynamic;

	UPROPERTY()
		UMaterialInterface* BrazierMaterial;

	UPROPERTY()
		UMaterialInstanceDynamic* BrazierMaterialDynamic;

	
	UPROPERTY()
		int CandlesAdded;


	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Interact_Implementation(AActor* InteractingActor) override;

	FString GetInteractMessage_Implementation() override;

	void UpdateAltarPreview(ACovenRisingCharacter* Character);

	void StopAltarPreview();

	void UpdateBrazierPreview(ACovenRisingCharacter* Character);

	void StopBrazierPreview();

	UPROPERTY()
		bool bIsAltarPlaced;

	UPROPERTY()
		bool bIsBrazierPlaced;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int PlacePentagramTime;

	UFUNCTION()
		void StartRitual();
};
