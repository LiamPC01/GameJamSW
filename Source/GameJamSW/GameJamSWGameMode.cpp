// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameJamSWGameMode.h"
#include "GameJamSWCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGameJamSWGameMode::AGameJamSWGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
