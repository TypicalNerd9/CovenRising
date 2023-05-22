// Fill out your copyright notice in the Description page of Project Settings.


#include "TownspersonPawn.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ATownspersonPawn::ATownspersonPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision Capsule"));
	SetRootComponent(CollisionComponent);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh Component"));
	Mesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ATownspersonPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATownspersonPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATownspersonPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

