// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "VillagerAIController.generated.h"

/**
 * 
 */
UCLASS()
class AVillagerAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AVillagerAIController();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAIPerceptionComponent* AIPerception;

	virtual void BeginPlay() override;
};
