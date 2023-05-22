// Fill out your copyright notice in the Description page of Project Settings.


#include "MortarAndPestleActor.h"

// Sets default values
AMortarAndPestleActor::AMortarAndPestleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Root Component")));

	MortarMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mortar Mesh"));
	MortarMeshComponent->SetupAttachment(RootComponent);

	PestleMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pestle Mesh"));
	PestleMeshComponent->SetupAttachment(MortarMeshComponent);
}

// Called when the game starts or when spawned
void AMortarAndPestleActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMortarAndPestleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMortarAndPestleActor::Interact_Implementation(AActor* InteractingActor)
{

}

FString AMortarAndPestleActor::GetInteractMessage_Implementation()
{
	return "Crush";
}

