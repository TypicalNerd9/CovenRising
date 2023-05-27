// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItemActor.h"
#include "SaltCellarItemActor.generated.h"

/**
 * 
 */
UCLASS()
class ASaltCellarItemActor : public ABaseItemActor
{
	GENERATED_BODY()
	
public:
	ASaltCellarItemActor();
protected:

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimSequence* PourSaltAnimation;

	
public:
	virtual void OnHeld() override;

	virtual void OnStoppedHolding() override;

	virtual void ConfirmTriggered() override;
};
