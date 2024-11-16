// Copyright Epic Games, Inc. All Rights Reserved.

#include "Slash_3rdPersonGameMode.h"
#include "Slash_3rdPersonCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASlash_3rdPersonGameMode::ASlash_3rdPersonGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
