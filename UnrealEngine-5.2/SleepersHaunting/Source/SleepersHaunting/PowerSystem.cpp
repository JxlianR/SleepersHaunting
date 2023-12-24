// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

#include "MyGameState.h"

#include "Net/UnrealNetwork.h"

APowerSystem::APowerSystem()
{
	PrimaryActorTick.bCanEverTick = true;
	bOnDepletion = false;
	bIsStopped = false;
	bLosingConditionDisplayed = false;
	// Create TextRenderComponent and attach it to the root
	TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRenderComponent"));
	TextRenderComponent->SetupAttachment(RootComponent);

	//Default
	TotalPower = 100.0f;  
	PowerConsumptionLow = 1.0f;
	PowerConsumptionMedium = 2.0f;
	PowerConsumptionHigh = 3.0f;
}

void APowerSystem::BeginPlay()
{
	Super::BeginPlay();
	GetAllInstanceClasses();
	// Initialize power values
	CurrentPower = TotalPower;
	
	PowerLevelConsumption = PowerConsumptionLow; // Default to low power consumption
	CurrentPowerLevel = EPowerLevel::Low; // Default to low power level
}

void APowerSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsStopped) // Check if not manually paused
	{
		// Update power level based on consumption
		if (CurrentPower > 0)
		{
			CurrentPower = FMath::Clamp(CurrentPower - PowerLevelConsumption * DeltaTime, 0.0f, TotalPower);
		}

		// Calculate power level percentage
		PowerLevelPercentage = (CurrentPower / TotalPower) * 100.0f;

		// Update TextRenderComponent
		FString PowerInfo = FString::Printf(TEXT("Power: %.0f%%\nLevel: %s"), PowerLevelPercentage, *UEnum::GetValueAsString(CurrentPowerLevel).RightChop(13));
		TextRenderComponent->SetText(FText::FromString(PowerInfo));

		// Check if power is depleted
		if (CurrentPower <= 0 && !bLosingConditionDisplayed )
		{
			// Losing Condition
			if (AMyGameStateInstance) {
				AMyGameStateInstance->SetLoseCondition(3);
			}
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Power Depleted!"));
			bLosingConditionDisplayed = true;

			bOnDepletion = false;
			bIsStopped = true;
		}
	}
}

void APowerSystem::GetAllInstanceClasses()
{
	if (AMyGameState* GameState = Cast<AMyGameState>(UGameplayStatics::GetGameState(GetWorld())))
	{
		AMyGameStateInstance = GameState;
	}
	else if (!AMyGameStateInstance)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Game State Instance not found!"));
	}
}

void APowerSystem::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(APowerSystem, CurrentPower);
	DOREPLIFETIME(APowerSystem, CurrentPowerLevel);
	//DOREPLIFETIME(APowerSystem, TextRenderComponent);
}

void APowerSystem::IncreasePowerConsumption()
{
	// Increase power consumption level (Low -> Medium -> High -> Loop back to Low)
	CurrentPowerLevel = static_cast<EPowerLevel>((static_cast<int32>(CurrentPowerLevel) + 1) % static_cast<int32>(EPowerLevel::Count));

	// Set the corresponding power consumption value based on the new level
	switch (CurrentPowerLevel)
	{
	case EPowerLevel::Low:
		PowerLevelConsumption = PowerConsumptionLow;
		break;
	case EPowerLevel::Medium:
		PowerLevelConsumption = PowerConsumptionMedium;
		break;
	case EPowerLevel::High:
		PowerLevelConsumption = PowerConsumptionHigh;
		break;
	default:
		break;
	}
}

void APowerSystem::DecreasePowerConsumption()
{
	// Decrease power consumption level (High -> Medium -> Low -> Loop back to High)
	CurrentPowerLevel = static_cast<EPowerLevel>((static_cast<int32>(CurrentPowerLevel) - 1 + static_cast<int32>(EPowerLevel::Count)) % static_cast<int32>(EPowerLevel::Count));

	// Set the corresponding power consumption value based on the new level
	switch (CurrentPowerLevel)
	{
	case EPowerLevel::Low:
		PowerLevelConsumption = PowerConsumptionLow;
		break;
	case EPowerLevel::Medium:
		PowerLevelConsumption = PowerConsumptionMedium;
		break;
	case EPowerLevel::High:
		PowerLevelConsumption = PowerConsumptionHigh;
		break;
	default:
		break;
	}
}

void APowerSystem::AddPower(float PowerToAdd)
{
	// Increment current power, but ensure it doesn't exceed the total power
	CurrentPower = FMath::Min(CurrentPower + PowerToAdd, TotalPower);
}

void APowerSystem::StopPower()
{
	bIsStopped = true;
}
