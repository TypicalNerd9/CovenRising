// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include <CovenRising/Private/BaseItemActor.h>
#include "ItemData.generated.h"

USTRUCT(BlueprintType)
struct FBaseItem {
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Data")
	FName ItemID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Data")
	FText Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Data")
	FText Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Data")
	UStaticMesh* Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Data")
	UTexture2D* Icon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Data")
	TSubclassOf<ABaseItemActor> Actor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Data")
	int32 MaxAmount;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Inventory")
	int32 Amount;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Inventory")
	int32 SlotNumber;

	FBaseItem() {
		Amount = 1;
	}
};

UCLASS(BlueprintType)
class UItemData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	TMap<FName, FBaseItem> Data;
};
