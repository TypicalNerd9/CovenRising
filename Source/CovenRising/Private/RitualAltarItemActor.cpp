// Fill out your copyright notice in the Description page of Project Settings.


#include "RitualAltarItemActor.h"
#include <CovenRising/CovenRisingCharacter.h>
#include <CovenRising/Private/RitualActor.h>

void ARitualAltarItemActor::Tick(float DeltaTime)
{
		ACovenRisingCharacter* Character = GetOwner<ACovenRisingCharacter>();
		if (Character) {
			FVector Location;
			FRotator Rotation;
			Character->GetController()->GetPlayerViewPoint(Location, Rotation);
			FHitResult hit;
			bool bHit = GetWorld()->LineTraceSingleByChannel(hit, Location, Location + Rotation.Vector() * 1000, ECC_Visibility);
			if (bHit) {
				ARitualActor* Ritual = Cast<ARitualActor>(hit.GetActor());
				if (Ritual && !Ritual->bIsAltarPlaced) {
					ViewedRitualActor = Ritual;
					Ritual->UpdateAltarPreview(Character);
				}
				else {
					if (ViewedRitualActor) {
						ViewedRitualActor->StopAltarPreview();
						ViewedRitualActor = nullptr;
					}
				}
			}
			else {
				if (ViewedRitualActor) {
					ViewedRitualActor->StopAltarPreview();
					ViewedRitualActor = nullptr;
				}
			}
		}
}


void ARitualAltarItemActor::OnStoppedHolding()
{
	if (ViewedRitualActor) {
		if (!ViewedRitualActor->bIsAltarPlaced) {
			ViewedRitualActor->StopAltarPreview();
			ViewedRitualActor = nullptr;
		}
	}
}
