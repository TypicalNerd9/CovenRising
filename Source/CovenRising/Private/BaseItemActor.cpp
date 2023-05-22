// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseItemActor.h"

// Sets default values
ABaseItemActor::ABaseItemActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Root Component")));
	ItemMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh"));
	ItemMeshComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABaseItemActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FString ABaseItemActor::GetItemId()
{
	return ItemId;
}

UStaticMeshComponent* ABaseItemActor::GetItemMeshComponent()
{
	return ItemMeshComponent;
}

