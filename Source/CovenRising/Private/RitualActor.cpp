// Fill out your copyright notice in the Description page of Project Settings.


#include "RitualActor.h"
#include "Components/DecalComponent.h"
#include <CovenRising/CovenRisingCharacter.h>
#include <CovenRising/Private/RitualAltarItemActor.h>
#include <CovenRising/Private/BrazierItemActor.h>
#include <CovenRising/Private/CandleActor.h>
#include <Runtime/Engine/Classes/Components/BoxComponent.h>

// Sets default values
ARitualActor::ARitualActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	RitualCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	SetRootComponent(RitualCollision);
	RitualCollision->InitBoxExtent(FVector(250, 250, 32));

	RitualCircleDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("Ritual Circle"));
	RitualCircleDecal->SetupAttachment(RootComponent);
	RitualCircleDecal->SetRelativeRotation(FRotator(90, 0, 0));
	RitualCircleDecal->SetRelativeScale3D(FVector(0.01, 1, 1));

	RitualAltar = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ritual Altar"));
	RitualAltar->SetupAttachment(RootComponent);
	RitualAltar->SetVisibility(false);

	Brazier = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Brazier"));
	Brazier->SetupAttachment(RootComponent);
	Brazier->SetVisibility(false);

	static ConstructorHelpers::FClassFinder<ACandleActor> CandleActorBP(TEXT("/Game/ThirdPerson/Blueprints/CandleActorBP"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CandlePlateMesh(TEXT("/Game/Assets/BuildingAssets/InteriorParts/Models/CandlePlate"));
	FVector CandleLocations[] = {FVector(-227, 74, 1), FVector(-136, -184, 1), FVector(132, -184, 1), FVector(224, 76, 1), FVector(0, 242, 1)};
	for (int i = 0; i < 5; i++) {
		FName CandleName = *FString::Printf(TEXT("Candle%i"), i+1);
		FName CandlePlateName = *FString::Printf(TEXT("CandlePlate%i"), i + 1);
		UChildActorComponent* Candle = CreateDefaultSubobject<UChildActorComponent>(CandleName);
		Candle->SetupAttachment(RootComponent);
		Candle->SetRelativeLocation(CandleLocations[i]);
		Candle->SetChildActorClass(CandleActorBP.Class);
		Candle->SetVisibility(false);
		Candle->ComponentTags.Add("Candle");
		UStaticMeshComponent* CandlePlate = CreateDefaultSubobject<UStaticMeshComponent>(CandlePlateName);
		CandlePlate->SetupAttachment(Candle);
		CandlePlate->SetStaticMesh(CandlePlateMesh.Object);
		CandlePlate->SetRelativeLocation(FVector(0, 0, -1));
		CandlePlate->SetVisibility(false);
	}

	CandlesAdded = 0;
}

// Called when the game starts or when spawned
void ARitualActor::BeginPlay()
{
	Super::BeginPlay();
	RitualAltarMaterial = RitualAltar->GetMaterial(0);
	RitualAltarMaterialDynamic = UMaterialInstanceDynamic::Create(RitualAltarMaterial, this);
	RitualAltar->SetMaterial(0, RitualAltarMaterialDynamic);
	RitualAltarMaterialDynamic->SetScalarParameterValue("Preview", 1);

	BrazierMaterial = Brazier->GetMaterial(0);
	BrazierMaterialDynamic = UMaterialInstanceDynamic::Create(BrazierMaterial, this);
	Brazier->SetMaterial(0, BrazierMaterialDynamic);
	BrazierMaterialDynamic->SetScalarParameterValue("Preview", 1);
}

// Called every frame
void ARitualActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARitualActor::Interact_Implementation(AActor* InteractingActor)
{
	ACovenRisingCharacter* Character = Cast<ACovenRisingCharacter>(InteractingActor);

	if (Character) {
		if (Character->GetHeldItemActor()) { 
			if (Character->GetHeldItemActor()->IsA(ARitualAltarItemActor::StaticClass())) {
				RitualAltarMaterialDynamic->SetScalarParameterValue("Preview", 0);
				bIsAltarPlaced = true;
				RitualAltar->SetVisibility(true);
				Character->TakeFromHeldItem(1);
			}
			else if (Character->GetHeldItemActor()->IsA(ABrazierItemActor::StaticClass())) {
				BrazierMaterialDynamic->SetScalarParameterValue("Preview", 0);
				bIsBrazierPlaced = true;
				Brazier->SetVisibility(true);
				Character->TakeFromHeldItem(1);
			}
			else if (Character->GetHeldItemActor()->GetItemId().Equals("candle")) {
				if (CandlesAdded < 5) {
					TArray<UActorComponent*> CandlesArray = GetComponentsByTag(UChildActorComponent::StaticClass(), "Candle");
					if (CandlesArray[CandlesAdded]) {
						UChildActorComponent* Candle = Cast<UChildActorComponent>(CandlesArray[CandlesAdded]);
						if (Candle) {
							Candle->SetVisibility(true, true);
							CandlesAdded++;
							Character->TakeFromHeldItem(1);
						}
					}
				}
			}
			else {
				if (bIsAltarPlaced) {
					TArray<UActorComponent*> IngredientArray = GetComponentsByTag(UActorComponent::StaticClass(), FName(*Character->GetHeldItemActor()->GetItemId()));
					if (!IngredientArray.IsEmpty()) {
						USceneComponent* Ingredient = Cast<USceneComponent>(IngredientArray[0]);
						if (Ingredient) {
							Ingredient->SetVisibility(true);
						}

					}
				}
			}
		}
	}
}

FString ARitualActor::GetInteractMessage_Implementation()
{
	return "Place";
}

void ARitualActor::UpdateAltarPreview(ACovenRisingCharacter* Character)
{
	if (!RitualAltar->IsVisible()) RitualAltar->SetVisibility(true);

	FVector LineVec = Character->GetActorLocation() - GetActorLocation();
	LineVec.Normalize();
	RitualAltar->SetRelativeRotation(FRotator(0, LineVec.Rotation().Yaw+90, LineVec.Rotation().Roll));
	RitualAltar->SetRelativeLocation(FVector(LineVec.X * 300, LineVec.Y * 300, 0));
}

void ARitualActor::StopAltarPreview()
{
	if (RitualAltar->IsVisible()) RitualAltar->SetVisibility(false);
}

void ARitualActor::UpdateBrazierPreview(ACovenRisingCharacter* Character)
{
	if (!Brazier->IsVisible()) Brazier->SetVisibility(true);

	FVector LineVec = Character->GetActorLocation() - GetActorLocation();
	LineVec.Normalize();
	Brazier->SetRelativeRotation(FRotator(0, LineVec.Rotation().Yaw + 90, LineVec.Rotation().Roll));
	Brazier->SetRelativeLocation(FVector(LineVec.X * 300, LineVec.Y * 300, 0));
}

void ARitualActor::StopBrazierPreview()
{
	if (Brazier->IsVisible()) Brazier->SetVisibility(false);
}

void ARitualActor::StartRitual()
{
}


