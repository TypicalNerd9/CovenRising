// Fill out your copyright notice in the Description page of Project Settings.


#include "VillagerAIController.h"
#include "Perception/AIPerceptionComponent.h"

AVillagerAIController::AVillagerAIController()
{
	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception"));
	
}

void AVillagerAIController::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(BehaviorTree);
}
