// Copyright Epic Games, Inc. All Rights Reserved.

#include "Flying509GameGameMode.h"
#include "Flying509GameCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFlying509GameGameMode::AFlying509GameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/AngelCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
