// Fill out your copyright notice in the Description page of Project Settings.


#include "CandleActor.h"
#include "NiagaraComponent.h"

// Sets default values
ACandleActor::ACandleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Root Component")));

	CandleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CandleMesh"));
	CandleMesh->SetupAttachment(RootComponent);

	FireParticle = CreateDefaultSubobject<UNiagaraComponent>(TEXT("FireParticle"));
	FireParticle->SetupAttachment(CandleMesh);
}

// Called when the game starts or when spawned
void ACandleActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACandleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

