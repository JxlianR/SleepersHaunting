// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "GameFramework/Actor.h"

//Place Other C++ classes here
#include "Roomba.h" //Julian needds to add code here.
#include "PlayerCharacter.h" //Also make the players here stop moving

#include "MyGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActivateUI);

/**
 * 
 */
UCLASS()
class SLEEPERSHAUNTING_API AMyGameState : public AGameState
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	AMyGameState();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	FOnActivateUI OnActivateUIEvent;
 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, Category = "Conditions")
		bool losingCondition;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, Category = "Conditions")
		bool winningCondition;

	//Classes
	class AA_FatherGarage* FatherGarageInstance;
	class ATheTwins* TheTwinsInstance_1;
	class ATheTwins* TheTwinsInstance_2;
	class ARoomba* RoombaInstance;
	class AClockTimer* ClockTimerInstance;
	class AGroupAttack* GroupAttackInstance;
	class APowerSystem* PowerSystemInstance;


	//APlayerCharacter* PlayerCharacterInstance; //Someone do this

	UFUNCTION()
		void SetLoseCondition(int nKiller);

	

	UFUNCTION()
		void WinConditionEvent();
private:
	UFUNCTION()
		void GetAllClassesInstances();
	UFUNCTION()
		void StopAllEventsTimers();
	//UFUNCTION()
		//void LoseConditionEvent();

};
