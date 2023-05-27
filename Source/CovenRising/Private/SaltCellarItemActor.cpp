// Fill out your copyright notice in the Description page of Project Settings.


#include "SaltCellarItemActor.h"
#include "Components/DecalComponent.h"
#include <CovenRising/CovenRisingCharacter.h>
#include <CovenRising/Private/SeanceRitualActor.h>
#include <CovenRisingGameInstance.h>
#include <CovenRising/Private/RitualData.h>

ASaltCellarItemActor::ASaltCellarItemActor()
{
	
}

void ASaltCellarItemActor::Tick(float DeltaTime)
{
	ACovenRisingCharacter* Character = GetOwner<ACovenRisingCharacter>();
	if (Character) {
		FVector Location;
		FRotator Rotation;
		Character->GetController()->GetPlayerViewPoint(Location, Rotation);
		FHitResult hit;
		bool bHit = GetWorld()->LineTraceSingleByChannel(hit, Location, Location + Rotation.Vector() * 1000, ECC_Visibility);
		if (bHit) {
			Character->PreviewDecal->SetWorldLocation(hit.Location);
		}
	}
}

void ASaltCellarItemActor::OnHeld()
{
	ACovenRisingCharacter* Character = GetOwner<ACovenRisingCharacter>();
	if (Character) {
		Character->PreviewDecal->SetVisibility(true);
	}
}

void ASaltCellarItemActor::OnStoppedHolding()
{
	ACovenRisingCharacter* Character = GetOwner<ACovenRisingCharacter>();
	if (Character) {
		Character->PreviewDecal->SetVisibility(false);
	}
}

void ASaltCellarItemActor::ConfirmTriggered()
{
	ACovenRisingCharacter* Character = GetOwner<ACovenRisingCharacter>();
	if (Character) {
		FVector Location;
		FRotator Rotation;
		Character->GetController()->GetPlayerViewPoint(Location, Rotation);
		FHitResult hit;
		bool bHit = GetWorld()->LineTraceSingleByChannel(hit, Location, Location + Rotation.Vector() * 1000, ECC_Visibility);
		if (bHit) {
			UCovenRisingGameInstance* GameInstance = GetGameInstance<UCovenRisingGameInstance>();
			if (GameInstance) {
				URitualData* RitualData = GameInstance->GetRitualDataAsset();
				if (RitualData) {
					FRitual SeanceRitual = RitualData->Data["seance"];
					ASeanceRitualActor* Ritual = GetWorld()->SpawnActor<ASeanceRitualActor>(SeanceRitual.Actor);
					Ritual->SetActorLocation(hit.Location);
					Ritual->StartDrawingPentagram();
					Character->PlayAnimation(PourSaltAnimation, Ritual->PlacePentagramTime);
					Character->TakeFromHeldItem(1);
				}
			}
			
		}
	}
}
