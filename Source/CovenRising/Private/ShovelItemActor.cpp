// Fill out your copyright notice in the Description page of Project Settings.


#include "ShovelItemActor.h"
#include <CovenRising/CovenRisingCharacter.h>


// Called every frame
void AShovelItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ACovenRisingCharacter* Character = GetOwner<ACovenRisingCharacter>();

	FVector RightHandLoc = Character->GetMesh()->GetSocketLocation(FName(TEXT("forearm_R_end")));
	FVector LeftHandLoc = Character->GetMesh()->GetSocketLocation(FName(TEXT("forearm_L_end")));
	FVector HandDiffVec = LeftHandLoc - RightHandLoc;
	HandDiffVec.Normalize();
	ItemMeshComponent->SetWorldRotation(FRotator(HandDiffVec.Rotation().Pitch, HandDiffVec.Rotation().Yaw, HandDiffVec.Rotation().Roll));
	ItemMeshComponent->SetRelativeRotation(FRotator(ItemMeshComponent->GetRelativeRotation().Pitch, ItemMeshComponent->GetRelativeRotation().Yaw, 0));

}