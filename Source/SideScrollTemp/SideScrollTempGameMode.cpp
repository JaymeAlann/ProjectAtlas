// Copyright Epic Games, Inc. All Rights Reserved.

#include "SideScrollTempGameMode.h"
#include "SideScrollTempCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASideScrollTempGameMode::ASideScrollTempGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
