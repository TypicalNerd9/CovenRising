// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItemActor.h"
#include <CovenRising/Private/RitualActor.h>
#include "BrazierItemActor.generated.h"

/**
 * 
 */
UCLASS()
class ABrazierItemActor : public ABaseItemActor
{
	GENERATED_BODY()
	
public:

protected:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
		ARitualActor* ViewedRitualActor;

public:
	virtual void OnStoppedHolding() override;
};
