// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameState.h"

//Classes
#include "A_FatherGarage.h"
#include "GroupAttack.h"
#include "TheTwins.h"
#include "ClockTimer.h"
#include "PowerSystem.h"

#include "Engine/World.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"


AMyGameState::AMyGameState() : 
	losingCondition(false)
{


	

}

// Called when the game starts or when spawned
void AMyGameState::BeginPlay()
{
	Super::BeginPlay();

	FatherGarageInstance = nullptr;
	TheTwinsInstance_1 = nullptr;
	TheTwinsInstance_2 = nullptr;
	ClockTimerInstance = nullptr;

	GetAllClassesInstances();
}

void AMyGameState::SetLoseCondition(int nKiller)
{
	//1 = TheTwins Jumpscare
	//2 = Father Jumpscare
	//3 = Power Jumpscare

	if (nKiller == 1) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("You Died from The Twins!"));
		ConditionText = FText::FromString("You Died from The Twins!");
		//Run the Twins jumpscare
	}
	else if (nKiller == 2) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("You Got Squashed from Father!"));
		ConditionText = FText::FromString("You Got Squashed from Father!");
		//Run the Father jumpscare
	}
	else if (nKiller == 3) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Oops no power oh well i guess i will die!"));
		ConditionText = FText::FromString("Oops no power oh well i guess i will die!");
		//Run the double twin jumpscare
	}
	
	StopAllEventsTimers();

	//Activate EndOfGameUI & Change Text
	OnActivateUIEvent.Broadcast(ConditionText);
}

void AMyGameState::WinConditionEvent()
{
	//Call a function to make it true or something
	
	StopAllEventsTimers();

	ConditionText = FText::FromString("You survived till 6 AM. Congratulations!");
	OnActivateUIEvent.Broadcast(ConditionText);
}

//Get All classes instances here
void AMyGameState::GetAllClassesInstances()
{
	// Get the world
	UWorld* World = GetWorld();
	if (World)
	{
		// Iterate over all actors in the world
		for (TActorIterator<AActor> ActorItr(World); ActorItr; ++ActorItr)
		{
			AActor* CurrentActor = *ActorItr;

			// Check the class of each actor
			if (AA_FatherGarage* FatherGarage = Cast<AA_FatherGarage>(CurrentActor))
			{
				FatherGarageInstance = FatherGarage;
			}
			else if (ATheTwins* Twins = Cast<ATheTwins>(CurrentActor))
			{
				if (!TheTwinsInstance_1)
				{
					TheTwinsInstance_1 = Twins;
				}
				else
				{
					TheTwinsInstance_2 = Twins;
				}
			}
			else if (AClockTimer* ClockTimer = Cast<AClockTimer>(CurrentActor))
			{
				ClockTimerInstance = ClockTimer;
			}
			else if (AGroupAttack* GroupAttack = Cast<AGroupAttack>(CurrentActor)) {
				GroupAttackInstance = GroupAttack;
			}
			else if (APowerSystem* PowerSystem = Cast<APowerSystem>(CurrentActor)) {
				PowerSystemInstance = PowerSystem;
			}
			else if (ARoomba* Roomba = Cast<ARoomba>(CurrentActor))
			{
				RoombaInstance = Roomba;
			}
		}
	}
}

void AMyGameState::StopAllEventsTimers()
{
	if (FatherGarageInstance)
	{
		FatherGarageInstance->StopAllTimers();
	}
	if (TheTwinsInstance_1)
	{
		TheTwinsInstance_1->PauseAllTwinTimers();
	}
	if (TheTwinsInstance_2)
	{
		TheTwinsInstance_2->PauseAllTwinTimers();
	}
	if (ClockTimerInstance)
	{
		ClockTimerInstance->StopTimer();
	}
	if (GroupAttackInstance)
	{
		GroupAttackInstance->CancelGroupAttackTimer();
	}
	if (PowerSystemInstance)
	{
		PowerSystemInstance->StopPower();
	}
	if (RoombaInstance)
	{
		RoombaInstance->SetStopped(true);
	}
}

/*
void AMyGameState::LoseConditionEvent()
{
	if (FatherGarageInstance) {
		FatherGarageInstance->StopAllTimers();
	}
	if (TheTwinsInstance_1) {
		TheTwinsInstance_1->PauseAllTwinTimers();
	}
	if (TheTwinsInstance_2) {
		TheTwinsInstance_2->PauseAllTwinTimers();
	}
	if (ClockTimerInstance) {
		ClockTimerInstance->StopTimer();
	}
	if (GroupAttackInstance) {
		GroupAttackInstance->CancelGroupAttackTimer();
	}
	if (PowerSystemInstance) {
		PowerSystemInstance->StopPower();
	}
}
*/

void AMyGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//DOREPLIFETIME(AMyGameState, losingCondition);
//DOREPLIFETIME(AMyGameState, winningCondition);
}


