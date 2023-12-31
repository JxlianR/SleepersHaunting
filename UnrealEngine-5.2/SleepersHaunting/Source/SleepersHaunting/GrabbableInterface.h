// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GrabbableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGrabbableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SLEEPERSHAUNTING_API IGrabbableInterface
{
	GENERATED_BODY()

public:
	FVector GetGrabLocation();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Grabbable")
	void Grab();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Grabbable")
	void Release();
};	