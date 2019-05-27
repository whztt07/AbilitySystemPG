// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "AbilitySystemPGGameMode.h"
#include "AbilitySystemPGHUD.h"
#include "AbilitySystemPGCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAbilitySystemPGGameMode::AAbilitySystemPGGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AAbilitySystemPGHUD::StaticClass();
}
