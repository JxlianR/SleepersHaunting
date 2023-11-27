// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "A_SecurityMonitor.h"
#include "A_SecuritySwitches.generated.h"

UCLASS()
class SLEEPERSHAUNTING_API AA_SecuritySwitches : public AActor
{
	GENERATED_BODY()

public:
	AA_SecuritySwitches();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Switch")
		bool IsLeftSwitch = true; // IF u want this to be a left switch which means (Previous camera)

public:
	UFUNCTION(BlueprintCallable, Category = "Switch")
		void ActivateSwitch();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Garage Handler")
		class AA_SecurityMonitor* FindSecurityCamera;

};

