// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryActorComponent.h"

// Sets default values for this component's properties
UInventoryActorComponent::UInventoryActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventoryActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventoryActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UInventoryActorComponent::AddItem(const FBaseItem& Item)
{
	for (int i = 0; i < InventoryArray.Num(); i++) {
		if (Item.ItemID == InventoryArray[i].ItemID) {
			if (InventoryArray[i].Amount < 64) {
				InventoryArray[i].Amount += Item.Amount;
				//InventoryArray[i].SlotNumber = 0;
				return true;
			}
		}
	}
	if (InventoryArray.Num() >= AmountOfSlots) return false;
	InventoryArray.Add(Item);
	//InventoryArray[InventoryArray.Num() - 1].SlotNumber = 0;
	return true;
}

int UInventoryActorComponent::GetSlotForItem(const FBaseItem& Item)
{
	return 0;
}

void UInventoryActorComponent::UpdateSlotNumber(UPARAM(ref) FBaseItem& Item, int32 NewSlotNumber)
{
	Item.SlotNumber = NewSlotNumber;
}

void UInventoryActorComponent::UpdateAmount(const FBaseItem& Item, int32 NewAmount)
{
	for (int i = 0; i < InventoryArray.Num(); i++) {
		if (Item.ItemID == InventoryArray[i].ItemID) {
			InventoryArray[i].Amount = NewAmount;
		}
	}
}

