// Fill out your copyright notice in the Description page of Project Settings.


#include "PlantActor.h"
#include <CovenRising/CovenRisingCharacter.h>
#include "Components/CapsuleComponent.h"
#include "ShovelItemActor.h"

// Sets default values
APlantActor::APlantActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Root Component")));

	CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision Capsule"));
	CollisionComponent->SetupAttachment(RootComponent);
	PlantMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plant Mesh"));
	PlantMeshComponent->SetupAttachment(CollisionComponent);

	ItemDropCount = 1;
}

// Called when the game starts or when spawned
void APlantActor::BeginPlay()
{
	Super::BeginPlay();
	
}


void APlantActor::AnimationEnded()
{
	bHasAnimationStarted = true;
}

// Called every frame
void APlantActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bHasAnimationStarted) {
		float Angle = FMath::Acos(FVector::DotProduct(FVector(0, 0, 1), HarvestDirectionVec));
		FVector Axis = FVector::CrossProduct(FVector(0, 0, 1), HarvestDirectionVec).GetSafeNormal();
		FQuat DeltaRotation = FQuat(Axis, Angle);
		HarvestDirectionVec.Normalize();
		SetActorLocation(FMath::VInterpTo(GetActorLocation(), GetActorLocation() + FVector(0, 0, 8) + (HarvestDirectionVec * 10), DeltaTime, 0.9f));
		SetActorRotation(FMath::QInterpTo(GetActorRotation().Quaternion(), DeltaRotation, DeltaTime, 1.2f));
		if (GetActorRotation().Quaternion().AngularDistance(DeltaRotation) < 0.2f) {
			Destroy();
		}
	}

}

void APlantActor::Interact_Implementation(AActor* InteractingActor)
{
	if (!bIsHarvested) {
		ACovenRisingCharacter* WitchCharacter = Cast<ACovenRisingCharacter>(InteractingActor);
		if (WitchCharacter) {
			if (WitchCharacter->GetHeldItemActor() && WitchCharacter->GetHeldItemActor()->IsA(AShovelItemActor::StaticClass())) {
				WitchCharacter->AddItemToInventory(ItemDropId, 1);
				WitchCharacter->AddItemToInventory(SeedDropId, FMath::RandRange(1, 4));
				WitchCharacter->PlayAnimation(WitchCharacter->DigAnimation, 3);
				HarvestDirectionVec = WitchCharacter->GetActorForwardVector();
				bIsHarvested = true;
				GetWorld()->GetTimerManager().SetTimer(HarvestTimer, this, &APlantActor::AnimationEnded, 1, false);
			}
		}
	}
}

FString APlantActor::GetInteractMessage_Implementation()
{
	return "Harvest";
}

