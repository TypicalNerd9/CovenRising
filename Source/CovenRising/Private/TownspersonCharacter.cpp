// Fill out your copyright notice in the Description page of Project Settings.

#include "TownspersonCharacter.h"

// Sets default values
ATownspersonCharacter::ATownspersonCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATownspersonCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATownspersonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATownspersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

