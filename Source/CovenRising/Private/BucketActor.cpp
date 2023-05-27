// Fill out your copyright notice in the Description page of Project Settings.


#include "BucketActor.h"
#include <CovenRising/Private/TankActorComponent.h>
#include <CovenRising/CovenRisingCharacter.h>
#include <Runtime/Engine/Classes/Kismet/KismetMathLibrary.h>
#include "NiagaraComponent.h"
#include "Components/TimelineComponent.h"
#include <CovenRising/Private/ItemData.h>
#include <CovenRising/Private/CovenRisingGameInstance.h>

// Sets default values
ABucketActor::ABucketActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Root Component")));

	BucketMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bucket Mesh"));
	BucketMeshComponent->SetupAttachment(RootComponent);

	WaterMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Water Mesh"));
	WaterMeshComponent->SetupAttachment(BucketMeshComponent);

	CleaningMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cleaning Mesh"));
	CleaningMeshComponent->SetupAttachment(BucketMeshComponent);

	CleaningTimelineComp = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimelineComponent"));
	CleaningTimelineComp->SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);

	CleaningDirtParticles = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Dirt Particles"));
	CleaningDirtParticles->SetupAttachment(CleaningMeshComponent);

	TankComponent = CreateDefaultSubobject<UTankActorComponent>(TEXT("Tank"));
	AddOwnedComponent(TankComponent);

	
}

// Called when the game starts or when spawned
void ABucketActor::BeginPlay()
{
	Super::BeginPlay();

	UpdateCleaningTrack.BindDynamic(this, &ABucketActor::UpdateCleaningMeshLocation);

	if (CleaningTimelineCurve)
	{
		CleaningTimelineComp->AddInterpFloat(CleaningTimelineCurve, UpdateCleaningTrack);
	}
	
}

void ABucketActor::AnimationEnded(ACovenRisingCharacter* Character)
{
	Character->SwitchToThirdPerson();
	//Character->SetHeldItemVisibility(true);
	CleaningMeshComponent->SetHiddenInGame(true);
	CleaningDirtParticles->SetHiddenInGame(true);
	Character->AddItemToInventory("valerian_roots", 1);
	bIsCleaning = false;
}

void ABucketActor::AnimationStarted(ACovenRisingCharacter* Character)
{
	Character->PlayAnimation(Character->CleanAnimation, 8);
	//Character->SetHeldItemVisibility(false);
	CleaningMeshComponent->SetHiddenInGame(false);
	CleaningDirtParticles->SetHiddenInGame(false);
	CleaningTimelineComp->PlayFromStart();
	FTimerDelegate Delegate;
	Delegate.BindUFunction(this, "AnimationEnded", Character);
	GetWorld()->GetTimerManager().SetTimer(CleaningTimer, Delegate, 7, false);
}

void ABucketActor::UpdateCleaningMeshLocation(float TimelineOutput)
{
	if (TimelineOutput <= -130) {
		FBaseItem CleanedItemData = *GetGameInstance<UCovenRisingGameInstance>()->GetItemDataAsset()->Data.Find("valerian_roots");
		CleaningMeshComponent->SetStaticMesh(CleanedItemData.Mesh);
	}
	CleaningMeshComponent->SetRelativeLocation(FVector(0, 0, 140+TimelineOutput));
}

// Called every frame
void ABucketActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABucketActor::Interact_Implementation(AActor* InteractingActor)
{
	if (!bIsCleaning) {
		ACovenRisingCharacter* WitchCharacter = Cast<ACovenRisingCharacter>(InteractingActor);
		if (WitchCharacter) {
			if (WitchCharacter->GetHeldItemActor() && WitchCharacter->GetHeldItemActor()->GetItemId() == "valerian_dirty_roots") {
				WitchCharacter->SwitchToFirstPerson();
				bIsCleaning = true;
				CleaningMeshComponent->SetStaticMesh(WitchCharacter->GetHeldItemActor()->GetItemMeshComponent()->GetStaticMesh());
				FVector DirectionVector = FVector(WitchCharacter->GetActorLocation().X, WitchCharacter->GetActorLocation().Y, 0) - FVector(GetActorLocation().X, GetActorLocation().Y, 0);
				DirectionVector.Normalize();
				DirectionVector *= 70;
				FRotator LookRotation = UKismetMathLibrary::FindLookAtRotation(WitchCharacter->GetActorLocation(), GetActorLocation());
				WitchCharacter->GetController()->SetControlRotation(FRotator(WitchCharacter->GetController()->GetControlRotation().Pitch, LookRotation.Yaw, LookRotation.Roll));
				WitchCharacter->SetActorLocation(GetActorLocation() + DirectionVector);
				WitchCharacter->TakeFromHeldItem(1);
				FTimerDelegate Delegate;
				Delegate.BindUFunction(this, "AnimationStarted", WitchCharacter);
				GetWorld()->GetTimerManager().SetTimer(StartCleaningTimer, Delegate, 1, false);
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("PICK UP"));
				WitchCharacter->AddItemToInventory(FName("bucket"), 1);
			}
		}
	}
}

FString ABucketActor::GetInteractMessage_Implementation()
{
	return "Clean";
}

