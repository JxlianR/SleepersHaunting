// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TimelineComponent.h"
#include "A_FatherGarage.generated.h"

UCLASS()
class SLEEPERSHAUNTING_API AA_FatherGarage : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AA_FatherGarage();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//UFUNCTION()
		//void OpenDoor();

	UFUNCTION(BlueprintCallable)
		void SetHandler1(bool NewValue);

	UFUNCTION(BlueprintCallable)
		void SetHandler2(bool NewValue);

	UFUNCTION(BlueprintCallable)
		void SetLosingConditionTrue();


	UFUNCTION()
		void StartCooldownTimer();

	UFUNCTION()
		void StartOpenDoorTimeline();

	UFUNCTION()
		void OnOpenDoorTimelineCompleted();


	UFUNCTION()
		void StartResetTimeline(); // Renamed from StartCloseDoorTimeline

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* GarageDoorMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float ZOffset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float OpenDoorDuration;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float ResetDoorDuration; // Renamed from CloseDoorDuration

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float CooldownDuration; // Added CooldownDuration

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
		UCurveFloat* OpenDoorCurve;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
		UCurveFloat* ResetDoorCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTimelineComponent* OpenDoorTimeline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTimelineComponent* ResetDoorTimeline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTimelineComponent* CooldownDoorTimeline;


	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
		//UCurveFloat* CooldownCurve;

	UPROPERTY(BlueprintReadOnly)
		bool bLosingCondition;

	UPROPERTY(BlueprintReadOnly)
		bool bHandler1;

	UPROPERTY(BlueprintReadOnly)
		bool bHandler2;

private:
	FVector InitialDoorLocation;
	FVector TargetDoorLocation;

	FTimerHandle CooldownTimerHandle;
	FTimerHandle OpenDoorTimerHandle;
	FTimerHandle ResetDoorTimerHandle;


	UFUNCTION()
		void OpenDoorUpdate(float Value);

	UFUNCTION()
		void ResetDoorUpdate(float Value); // Renamed from CloseDoorUpdate

	//UFUNCTION()
		//void CooldownDoorUpdate(float Value);

	//UFUNCTION()
		//void StartResetDoorTimer();

	//UFUNCTION()
		//void ResetDoor();
};