// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CandleActor.generated.h"

UCLASS()
class ACandleActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACandleActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Candle Details")
	UStaticMeshComponent* CandleMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Candle Details")
	class UNiagaraComponent* FireParticle;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
