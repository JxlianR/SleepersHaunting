// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

APowerSystem::APowerSystem()
{
	PrimaryActorTick.bCanEverTick = true;
	bPauseOnDepletion = false;

	// Create TextRenderComponent and attach it to the root
	TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRenderComponent"));
	TextRenderComponent->SetupAttachment(RootComponent);
}

void APowerSystem::BeginPlay()
{
	Super::BeginPlay();

	// Initialize power values
	TotalPower = 100.0f;  // Set your desired total power value
	CurrentPower = TotalPower;
	PowerConsumptionLow = 1.0f;
	PowerConsumptionMedium = 2.0f;
	PowerConsumptionHigh = 3.0f;
	PowerLevelConsumption = PowerConsumptionLow; // Default to low power consumption

	// Set initial power level
}

void APowerSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsPaused) // Check if not manually paused
	{
		// Update power level based on consumption
		if (CurrentPower > 0)
		{
			CurrentPower -= PowerLevelConsumption * DeltaTime;
		}

		// Calculate power level percentage
		PowerLevelPercentage = (CurrentPower / TotalPower) * 100.0f;

		// Update TextRenderComponent
		FString PowerInfo = FString::Printf(TEXT("Power: %.2f / %.2f\nConsumption: %.2f\nRemaining: %.2f%%"),
			CurrentPower, TotalPower, PowerLevelConsumption, PowerLevelPercentage);
		TextRenderComponent->SetText(FText::FromString(PowerInfo));

		// Check if power is depleted
		if (CurrentPower <= 0)
		{
			// Handle power depletion (e.g., trigger blackout, game over, etc.)
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Power Depleted!"));

			// Automatically pause the power system when bPauseOnDepletion is true
			if (bPauseOnDepletion)
			{
				bIsPaused = true;
			}
		}
	}
}

void APowerSystem::PausePowerSystem()
{
	bIsPaused = true;
}

void APowerSystem::ResumePowerSystem()
{
	bIsPaused = false;
}