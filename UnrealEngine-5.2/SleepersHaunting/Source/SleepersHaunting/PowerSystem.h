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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UTextRenderComponent* TextRenderComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Power")
		float TotalPower;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Power", Replicated)
		float CurrentPower;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Power")
		float PowerConsumptionLow;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Power")
		float PowerConsumptionMedium;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Power")
		float PowerConsumptionHigh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Power")
		float PowerLevelPercentage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Power")
		float PowerLevelConsumption;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Power", Replicated)
		EPowerLevel CurrentPowerLevel;

	UPROPERTY(EditAnywhere, Category = "Power")
		bool bOnDepletion;

	class AMyGameState* AMyGameStateInstance;

private:
	UFUNCTION()
		void GetAllInstanceClasses();

	bool bIsStopped;
	bool bLosingConditionDisplayed;
};