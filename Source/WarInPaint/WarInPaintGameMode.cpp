// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "WarInPaintGameMode.h"
#include "WarInPaintHUD.h"
#include "WarInPaintCharacter.h"
#include "UObject/ConstructorHelpers.h"

AWarInPaintGameMode::AWarInPaintGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AWarInPaintHUD::StaticClass();
}
