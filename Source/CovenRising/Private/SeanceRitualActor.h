// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RitualActor.h"
#include <Runtime/Engine/Classes/Components/TimelineComponent.h>
#include "SeanceRitualActor.generated.h"

/**
 * 
 */
UCLASS()
class ASeanceRitualActor : public ARitualActor
{
	GENERATED_BODY()
	
public:
	ASeanceRitualActor();
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* Skull;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCurveFloat* PentagramTimelineCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTimelineComponent* SaltPentagramTimelineComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMaterialInterface* SaltPentagramMaterial;

	UPROPERTY()
	UMaterialInstanceDynamic* SaltPentagramMaterialDynamic;

	FOnTimelineFloat UpdateSaltPentagramTrack;

	virtual void BeginPlay() override;

	UFUNCTION()
		void UpdatePentagramOpacity(float TimelineOutput);

public:
	UFUNCTION()
		void StartDrawingPentagram();
};
