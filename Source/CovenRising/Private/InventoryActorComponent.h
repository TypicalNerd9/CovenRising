// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <CovenRising/Private/ItemData.h>
#include "InventoryActorComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UInventoryActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inventory)
	TArray<struct FBaseItem> InventoryArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inventory)
	int NumberOfRows;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inventory)
	int NumberOfColumns;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inventory)
	int AmountOfSlots;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	bool AddItem(const FBaseItem& Item);

	int GetSlotForItem(const FBaseItem& Item);

	UFUNCTION(BlueprintCallable)
		void UpdateSlotNumber(UPARAM(ref) FBaseItem& Item, int32 NewSlotNumber);

	UFUNCTION(BlueprintCallable)
		void UpdateAmount(const FBaseItem& Item, int32 NewAmount);
};
