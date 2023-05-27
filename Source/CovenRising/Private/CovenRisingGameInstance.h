// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CovenRisingGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UCovenRisingGameInstance : public UGameInstance
{
	GENERATED_BODY()
	

	protected:
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Items")
		class UItemData* ItemDataAsset;

		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Rituals")
			class URitualData* RitualDataAsset;

	public:
		UFUNCTION(BlueprintCallable)
		UItemData* GetItemDataAsset();

		UFUNCTION(BlueprintCallable)
			URitualData* GetRitualDataAsset();
};
