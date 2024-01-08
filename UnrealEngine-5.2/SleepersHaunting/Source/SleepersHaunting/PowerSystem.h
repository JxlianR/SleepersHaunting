// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "PowerSystem.generated.h"

UENUM(BlueprintType)
enum class EPowerLevel : uint8
{
	Low UMETA(DisplayName = "Low"),
	Medium UMETA(DisplayName = "Medium"),
	High UMETA(DisplayName = "High"),
	Count UMETA(Hidden)
};

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

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable, Category = "Power")
	void IncreasePowerConsumption();

	UFUNCTION(BlueprintCallable, Category = "Power")
	void DecreasePowerConsumption();

	UFUNCTION(BlueprintCallable, Category= "Power")
	void AddPower(float PowerToAdd);

	UFUNCTION()
	void StopPower();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"), Replicated)
		UTextRenderComponent* TextRenderComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Power")
		float TotalPower = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Power", Replicated)
		float CurrentPower = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Power")
		float PowerConsumptionLow = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Power")
		float PowerConsumptionMedium = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Power")
		float PowerConsumptionHigh = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Power")
		float PowerLevelPercentage = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Power")
		float PowerLevelConsumption = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Power", Replicated)
		EPowerLevel CurrentPowerLevel = EPowerLevel::Low;

	UPROPERTY(EditAnywhere, Category = "Power")
		bool bOnDepletion = false;

	UPROPERTY()
	class AMyGameState* AMyGameStateInstance = nullptr;

private:
	UFUNCTION()
		void GetAllInstanceClasses();

	bool bIsStopped = false;
	bool bLosingConditionDisplayed = false;
};