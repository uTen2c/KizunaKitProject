// Copyright Epic Games, Inc. All Rights Reserved.

#include "KizunaKitProjectGameMode.h"
#include "KizunaKitProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AKizunaKitProjectGameMode::AKizunaKitProjectGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
