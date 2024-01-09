// Copyright Epic Games, Inc. All Rights Reserved.


#include "SleepersHauntingGameModeBase.h"
#include "MyGameState.h"

//#include "MyGameState.h"

ASleepersHauntingGameModeBase::ASleepersHauntingGameModeBase() {
	GameStateClass = AMyGameState::StaticClass();

	
}

void ASleepersHauntingGameModeBase::CallServerTravel()
{
	UWorld* World = GetWorld();
	World->ServerTravel("ModeLel");
}
