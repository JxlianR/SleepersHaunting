// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GrabbableInterface.generated.h"

UINTERFACE(MinimalAPI)
class UGrabbableInterface : public UInterface
{
	GENERATED_BODY()
};

class SLEEPERSHAUNTING_API IGrabbableInterface
{
	GENERATED_BODY()

public:
    // Function to grab the object
    virtual void GrabObject(ACharacter* PlayerCharacter) = 0;

    // Function to release the object
    virtual void ReleaseObject() = 0;
};	