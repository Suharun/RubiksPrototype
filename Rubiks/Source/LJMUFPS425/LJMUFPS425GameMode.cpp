// Copyright Epic Games, Inc. All Rights Reserved.

#include "LJMUFPS425GameMode.h"
#include "LJMUFPS425HUD.h"
#include "LJMUFPS425Character.h"
#include "UObject/ConstructorHelpers.h"

ALJMUFPS425GameMode::ALJMUFPS425GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ALJMUFPS425HUD::StaticClass();
}
