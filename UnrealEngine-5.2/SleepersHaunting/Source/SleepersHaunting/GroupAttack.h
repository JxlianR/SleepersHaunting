// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GroupAttack.generated.h"

UCLASS()
class SLEEPERSHAUNTING_API AGroupAttack : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGroupAttack();
	
	// Duration for attack cooldown
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Group Attack")
		float SattackTimer = 1.0f;

	UFUNCTION(BlueprintCallable, Category = "Audio")
	void PlayGroupAttackSound();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Group Attack")
		class ATheTwins* TheTwinsInstance_1 = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Group Attack")
		class ATheTwins* TheTwinsInstance_2 = nullptr;

	UFUNCTION()
		void AttemptGroupAttack(bool whichTwin); //true for left, false for right
	UFUNCTION()
		void LeaveAttemptGroupAttack(bool whichTwin); //true for left, false for right
	UFUNCTION()
		void CancelGroupAttackTimer();

	UFUNCTION()
		void TryGroupAttack();

	UPROPERTY()
	class AMyGameState* AMyGameStateInstance = nullptr;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Audio")
	class USoundCue* GroundAttackSoundCue = nullptr;

private:
	bool LeftTwinAtk = false;
	bool RightTwinAtk = false;

	FTimerHandle SAttackTimerHandle;


	void GetAllInstanceClasses();



};
