// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "A_FatherGarage.h"
#include "Net/UnrealNetwork.h"

#include "GarageHandler.generated.h"

UCLASS()
class SLEEPERSHAUNTING_API AGarageHandler : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGarageHandler();

	// Function to set the value of bHandler1
	UFUNCTION(BlueprintCallable, Category = "Garage Handler")
		void SetHandlerFalse();
	UFUNCTION(BlueprintCallable, Category = "Garage Handler")
		void SetHandlerTrue();

	// Reference to the garage class
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Garage Handler")
		class AA_FatherGarage* GarageReference = nullptr;

	// Boolean to determine if this represents bHandler1 or bHandler2
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Garage Handler")
		bool bIsHandler1 = false;

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

};