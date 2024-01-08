// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "Net/UnrealNetwork.h"
#include "ClockTimer.generated.h"


UCLASS()
class SLEEPERSHAUNTING_API AClockTimer : public AActor
{
	GENERATED_BODY()

public:
	AClockTimer();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Timer")
		float CountdownTime = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Timer")
		bool bWinCondition = false;

	UFUNCTION(BlueprintCallable, Category = "Timer")
		void StopTimer();

	class AMyGameState* AMyGameStateInstance;

private:
	UFUNCTION()
		void GetAllInstanceClasses();

	UPROPERTY(Replicated)
	float ElapsedTime = 0.0f;

	UPROPERTY(Replicated)
	bool bShouldTick = false;

	// TextRenderComponent for displaying the time
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UTextRenderComponent* TextRenderComponent = nullptr;

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;
};
