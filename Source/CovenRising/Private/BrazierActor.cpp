// Fill out your copyright notice in the Description page of Project Settings.


#include "BrazierActor.h"
#include <Runtime/Engine/Classes/Components/BoxComponent.h>
#include <Niagara/Public/NiagaraComponent.h>
#include <CovenRising/Private/RitualActor.h>

// Sets default values
ABrazierActor::ABrazierActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Root")));

	Brazier = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Brazier Mesh"));
	Brazier->SetupAttachment(RootComponent);

	BrazierCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Brazier Collision"));
	BrazierCollision->SetupAttachment(Brazier);

	Flame = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Flame Particle"));
	Flame->SetupAttachment(Brazier);
	Flame->SetAutoActivate(false);
}

// Called when the game starts or when spawned
void ABrazierActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABrazierActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABrazierActor::Interact_Implementation(AActor* InteractingActor)
{
	if (!bIsLit) {
		Flame->SetActive(true);
		bIsLit = true;
		RitualActor->StartRitual();
	}
}

FString ABrazierActor::GetInteractMessage_Implementation()
{
	return "Light";
}

