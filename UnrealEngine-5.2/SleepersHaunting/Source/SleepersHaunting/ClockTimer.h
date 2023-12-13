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
		float CountdownTime;

	UPROPERTY(BlueprintReadOnly, Category = "Timer")
		bool bWinCondition;

private:
	UPROPERTY(Reliable)
	float ElapsedTime;

	// TextRenderComponent for displaying the time
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UTextRenderComponent* TextRenderComponent;

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;
};
