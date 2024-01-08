// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "GameFramework/Actor.h"

//Place Other C++ classes here
#include "Roomba.h" //Julian needds to add code here.
#include "PlayerCharacter.h" //Also make the players here stop moving

#include "MyGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActivateUI, FText, NewText);

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



	void StopAllSounds();

	FOnActivateUI OnActivateUIEvent;
 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, Category = "Conditions")
		bool losingCondition = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, Category = "Conditions")
		bool winningCondition = false;

	//Classes
	UPROPERTY()
	class AA_FatherGarage* FatherGarageInstance = nullptr;

	UPROPERTY()
	class ATheTwins* TheTwinsInstance_1 = nullptr;

	UPROPERTY()
	class ATheTwins* TheTwinsInstance_2 = nullptr;

	UPROPERTY()
	class ARoomba* RoombaInstance = nullptr;

	UPROPERTY()
	class AClockTimer* ClockTimerInstance = nullptr;

	UPROPERTY()
	class AGroupAttack* GroupAttackInstance = nullptr;

	UPROPERTY()
	class APowerSystem* PowerSystemInstance = nullptr;


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

	UPROPERTY()
	FText ConditionText;
};
