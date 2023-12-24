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
		float SattackTimer;



	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Group Attack")
		class ATheTwins* TheTwinsInstance_1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Group Attack")
		class ATheTwins* TheTwinsInstance_2;

	UFUNCTION()
		void AttemptGroupAttack(bool whichTwin); //true for left, false for right
	UFUNCTION()
		void LeaveAttemptGroupAttack(bool whichTwin); //true for left, false for right
	UFUNCTION()
		void CancelGroupAttackTimer();

	UFUNCTION()
		void TryGroupAttack();

	class AMyGameState* AMyGameStateInstance;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	float LeftTwinAtk;
	float RightTwinAtk;

	FTimerHandle SAttackTimerHandle;


	void GetAllInstanceClasses();



};
