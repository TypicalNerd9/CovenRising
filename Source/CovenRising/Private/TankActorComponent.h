// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UTankActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tank Info")
	int CurrentCapacity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tank Info")
	int MaxCapacity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tank Info")
	bool Empty;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tank Info")
	class UStaticMeshComponent* WaterMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tank Info")
		int MaxWaterHeight;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable)
		void EmptyTank();

	UFUNCTION(BlueprintCallable)
		bool TransferSubstance(UTankActorComponent* ReceivingTank, int AmountTransferred);

	UFUNCTION(BlueprintCallable)
		bool RemoveSubstance(int AmountRemoved);

	UFUNCTION(BlueprintCallable)
		bool AddSubstance(int AmountAdded);
		
	UFUNCTION()
		void SetWaterMesh(UStaticMeshComponent* MeshComponent);
};
