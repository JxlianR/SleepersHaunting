// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"
#include "UObject/Interface.h"
#include "JumpableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UJumpableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SLEEPERSHAUNTING_API IJumpableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void JumpedOn(APlayerCharacter* Character);
};
