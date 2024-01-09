// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"




#include "SleepersHauntingGameModeBase.generated.h"


UCLASS()
class SLEEPERSHAUNTING_API ASleepersHauntingGameModeBase : public AGameMode
{
	GENERATED_BODY()

public:
	ASleepersHauntingGameModeBase();
	//virtual ~ASleepersHauntingGameModeBase() = default; // ~ is a destructor

	UFUNCTION()
	void CallServerTravel();

};
