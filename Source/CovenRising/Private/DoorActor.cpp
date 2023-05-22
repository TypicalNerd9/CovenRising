// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorActor.h"

// Sets default values
ADoorActor::ADoorActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Root Component")));

	DoorMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Mesh"));
	DoorMeshComponent->SetupAttachment(RootComponent);

	DoorTimelineComp = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimelineComponent"));
	DoorTimelineComp->SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);
}

// Called when the game starts or when spawned
void ADoorActor::BeginPlay()
{
	Super::BeginPlay();

	UpdateDoorTrack.BindDynamic(this, &ADoorActor::UpdateDoorRotation);

	if (DoorTimelineCurve)
	{
		DoorTimelineComp->AddInterpFloat(DoorTimelineCurve, UpdateDoorTrack);
	}
	OriginalDoorRotation = GetActorRotation();
}

void ADoorActor::UpdateDoorRotation(float TimelineOutput)
{
	SetActorRotation(OriginalDoorRotation + FRotator(0, FMath::Lerp(0.0f, FacingDirection*110.0f, TimelineOutput), 0));
	
}

// Called every frame
void ADoorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoorActor::Interact_Implementation(AActor* InteractingActor)
{
	if (!DoorTimelineComp->IsPlaying()) {
		if (!bIsOpen) {
			if (GetActorForwardVector().Dot(GetActorLocation()-InteractingActor->GetActorLocation()) > 0)
				FacingDirection = 1;
			else
				FacingDirection = -1;
			DoorTimelineComp->PlayFromStart();
			bIsOpen = true;
		}
		else {
			DoorTimelineComp->ReverseFromEnd();
			bIsOpen = false;
		}
	}
}

FString ADoorActor::GetInteractMessage_Implementation()
{
	if (bIsOpen) return "Close";
	return "Open";
}

