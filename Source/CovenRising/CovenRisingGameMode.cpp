// Copyright Epic Games, Inc. All Rights Reserved.

#include "CovenRisingGameMode.h"
#include "CovenRisingCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACovenRisingGameMode::ACovenRisingGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
