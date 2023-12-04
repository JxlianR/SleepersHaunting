// Fill out your copyright notice in the Description page of Project Settings.

#include "ClockTimer.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

AClockTimer::AClockTimer()
{
	PrimaryActorTick.bCanEverTick = true;
	bWinCondition = false;

	// Create TextRenderComponent and attach it to the root
	TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRenderComponent"));
	TextRenderComponent->SetupAttachment(RootComponent);
}

void AClockTimer::BeginPlay()
{
	Super::BeginPlay();
	ElapsedTime = 0.0f;
	TextRenderComponent->SetText(FText::FromString("12:00 AM"));
}

void AClockTimer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ElapsedTime += DeltaTime;

	// Calculate the remaining time
	float RemainingTimeFraction = FMath::Clamp(ElapsedTime / CountdownTime, 0.0f, 1.0f);

	// Convert the fraction to hours
	int32 RemainingHours = FMath::RoundToInt(6 * RemainingTimeFraction);
	FString TimeString = FString::Printf(TEXT("%2d:00 AM"), RemainingHours);
	TextRenderComponent->SetText(FText::FromString(TimeString));

	// If countdown finished
	if (ElapsedTime >= CountdownTime && !bWinCondition)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("You Survived!"));
		bWinCondition = true;
		UGameplayStatics::OpenLevel(GetWorld(), FName("WinMenu"));
		//Also make it here to stop all other timers and Ai
	}
}