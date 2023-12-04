// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"

#include "PowerSystem.generated.h"

UCLASS()
class SLEEPERSHAUNTING_API APowerSystem : public AActor
{
	GENERATED_BODY()

public:
	APowerSystem();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Power")
		void PausePowerSystem();

	UFUNCTION(BlueprintCallable, Category = "Power")
		void ResumePowerSystem();

	UPROPERTY(EditAnywhere, Category = "Power")
		float TotalPower;

	UPROPERTY(EditAnywhere, Category = "Power")
		float CurrentPower;

	UPROPERTY(EditAnywhere, Category = "Power")
		float PowerConsumptionLow;

	UPROPERTY(EditAnywhere, Category = "Power")
		float PowerConsumptionMedium;

	UPROPERTY(EditAnywhere, Category = "Power")
		float PowerConsumptionHigh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UTextRenderComponent* TextRenderComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Power")
		float PowerLevelPercentage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Power")
		float PowerLevelConsumption;

	UPROPERTY(EditAnywhere, Category = "Power")
		bool bPauseOnDepletion;

private:
	bool bIsPaused;
};
