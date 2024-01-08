// Fill out your copyright notice in the Description page of Project Settings.

#include "ClockTimer.h"
#include "MyGameState.h"

#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

AClockTimer::AClockTimer()
{
	PrimaryActorTick.bCanEverTick = true;
	bWinCondition = false;
	bShouldTick = true;

	// Create TextRenderComponent and attach it to the root
	TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRenderComponent"));
	TextRenderComponent->SetupAttachment(RootComponent);
}

void AClockTimer::BeginPlay()
{
	Super::BeginPlay();
	ElapsedTime = 0.0f;
	GetAllInstanceClasses();
	if (TextRenderComponent)
		TextRenderComponent->SetText(FText::FromString("12:00 AM"));
}

void AClockTimer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bShouldTick) {
		ElapsedTime += DeltaTime;

		// Calculate the remaining time
		float RemainingTimeFraction = FMath::Clamp(ElapsedTime / CountdownTime, 0.0f, 1.0f);

		// Convert the fraction to hours
		int32 RemainingHours = FMath::RoundToInt(6 * RemainingTimeFraction);
		FString TimeString = FString::Printf(TEXT("%2d:00 AM"), RemainingHours);

		if (TextRenderComponent)
			TextRenderComponent->SetText(FText::FromString(TimeString));

		// If countdown finished
		if (ElapsedTime >= CountdownTime && !bWinCondition)
		{
			if (AMyGameStateInstance) {
				AMyGameStateInstance->WinConditionEvent();
			}
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("You Survived!"));
			bWinCondition = true;
			UGameplayStatics::OpenLevel(GetWorld(), FName("WinMenu"));
			//Also make it here to stop all other timers and Ai
		}
	}
	
}

void AClockTimer::StopTimer()
{
	bShouldTick = false;		
}

void AClockTimer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AClockTimer, ElapsedTime);
	DOREPLIFETIME(AClockTimer, bShouldTick);

}

void AClockTimer::GetAllInstanceClasses()
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