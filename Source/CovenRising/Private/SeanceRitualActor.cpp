// Fill out your copyright notice in the Description page of Project Settings.


#include "SeanceRitualActor.h"
#include "Components/DecalComponent.h"

ASeanceRitualActor::ASeanceRitualActor()
{
	Skull = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Skull"));
	Skull->SetupAttachment(RitualAltar);
	Skull->SetVisibility(false);

	SaltPentagramTimelineComp = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimelineComponent"));
	SaltPentagramTimelineComp->SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);
}

void ASeanceRitualActor::BeginPlay()
{
	Super::BeginPlay();

	SaltPentagramMaterialDynamic = UMaterialInstanceDynamic::Create(SaltPentagramMaterial, this);
	RitualCircleDecal->SetMaterial(0, SaltPentagramMaterialDynamic);

	SaltPentagramTimelineComp->SetPlayRate(16.0 / PlacePentagramTime);

	UpdateSaltPentagramTrack.BindDynamic(this, &ASeanceRitualActor::UpdatePentagramOpacity);

	if (PentagramTimelineCurve)
	{
		SaltPentagramTimelineComp->AddInterpFloat(PentagramTimelineCurve, UpdateSaltPentagramTrack);
	}

} 

void ASeanceRitualActor::UpdatePentagramOpacity(float TimelineOutput)
{
	SaltPentagramMaterialDynamic->SetScalarParameterValue("Opacity", TimelineOutput);
}

void ASeanceRitualActor::StartDrawingPentagram()
{
	SaltPentagramTimelineComp->PlayFromStart();
}
