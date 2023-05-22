// Fill out your copyright notice in the Description page of Project Settings.


#include "TankActorComponent.h"

// Sets default values for this component's properties
UTankActorComponent::UTankActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (WaterMesh && CurrentCapacity > 0 && Empty) {
		Empty = false;
		WaterMesh->SetVisibility(true);
	}
	
	if (CurrentCapacity == 0 && WaterMesh && !Empty) {
		Empty = true;
		WaterMesh->SetVisibility(false);
	}
}

void UTankActorComponent::EmptyTank()
{
	if (CurrentCapacity > 0) {
		CurrentCapacity = 0;
	}
}

bool UTankActorComponent::TransferSubstance(UTankActorComponent* ReceivingTank, int AmountTransferred)
{
	if (WaterMesh && CurrentCapacity >= AmountTransferred && ReceivingTank->CurrentCapacity + AmountTransferred <= ReceivingTank->MaxCapacity) {
		ReceivingTank->AddSubstance(AmountTransferred);
		RemoveSubstance(AmountTransferred);
		return true;
	}
	return false;
}

bool UTankActorComponent::RemoveSubstance(int AmountRemoved)
{
	if (WaterMesh && CurrentCapacity >= AmountRemoved) {
		CurrentCapacity -= AmountRemoved;
		WaterMesh->SetRelativeLocation(FVector(0, 0, CurrentCapacity * MaxWaterHeight / MaxCapacity));
		return true;
	}
	return false;
}

bool UTankActorComponent::AddSubstance(int AmountAdded)
{
	if (WaterMesh && CurrentCapacity + AmountAdded <= MaxCapacity) {
		CurrentCapacity += AmountAdded;
		WaterMesh->SetRelativeLocation(FVector(0, 0, CurrentCapacity * MaxWaterHeight / MaxCapacity));
		return true;
	}
	return false;
}

void UTankActorComponent::SetWaterMesh(UStaticMeshComponent* MeshComponent)
{
	WaterMesh = MeshComponent;
}

