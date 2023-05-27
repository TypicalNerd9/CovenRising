// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include <CovenRising/Private/RitualActor.h>
#include "RitualData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FRitual {
	GENERATED_BODY()

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ritual Data")
		FName RitualId;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ritual Data")
		FText Name;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ritual Data")
		UTexture2D* Icon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ritual Data")
		TSubclassOf<ARitualActor> Actor;
};

UCLASS()
class URitualData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ritual Data")
		TMap<FName, FRitual> Data;
};
