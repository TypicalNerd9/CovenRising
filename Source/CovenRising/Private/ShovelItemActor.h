// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItemActor.h"
#include "ShovelItemActor.generated.h"

/**
 * 
 */
UCLASS()
class AShovelItemActor : public ABaseItemActor
{
	GENERATED_BODY()
	
public:
	

protected:

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
