// Fill out your copyright notice in the Description page of Project Settings.


#include "BrazierItemActor.h"
#include <CovenRising/CovenRisingCharacter.h>
#include <CovenRising/Private/RitualActor.h>

void ABrazierItemActor::Tick(float DeltaTime)
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
			if (Ritual && !Ritual->bIsBrazierPlaced) {
				ViewedRitualActor = Ritual;
				Ritual->UpdateBrazierPreview(Character);
			}
			else {
				if (ViewedRitualActor) {
					ViewedRitualActor->StopBrazierPreview();
					ViewedRitualActor = nullptr;
				}
			}
		}
		else {
			if (ViewedRitualActor) {
				ViewedRitualActor->StopBrazierPreview();
				ViewedRitualActor = nullptr;
			}
		}
	}
}


void ABrazierItemActor::OnStoppedHolding()
{
	if (ViewedRitualActor) {
		if (!ViewedRitualActor->bIsBrazierPlaced) {
			ViewedRitualActor->StopBrazierPreview();
			ViewedRitualActor = nullptr;
		}
	}
}

