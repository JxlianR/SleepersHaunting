// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "A_FatherGarage.generated.h"
//#include "Components/StaticMeshComponent.h"
//#include "Components/TimelineComponent.h"


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
	/*
	UFUNCTION()
		void OnInteractedPressed();

	UFUNCTION()
		void CoolDoorUpdate(float value);

	UFUNCTION()
		void OpenDoorUpdate(float value);

	UFUNCTION()
		void ResetDoorUpdate(float value);
		*/

private:
	/*
	UPROPERTY(EditAnywhere)
		float ZOffset; //Adds plus the initial location of the z.
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* GarageDoorMesh;

	UPROPERTY(EditAnywhere)
		UCurveFloat* CooldownCurve;

	UPROPERTY(EditAnywhere)
		UCurveFloat* OpenDoorCurve;

	UPROPERTY(EditAnywhere)
		UCurveFloat* ResetDoorCurve;

	UPROPERTY(EditAnywhere)
		float TargetDoorLocation;

	UPROPERTY(EditAnywhere)
		FVector InitialDoorLocation; //Use this to store the initial postion of the garage door

	UPROPERTY(EditAnywhere)
		float bCanInteract;

	UPROPERTY(EditAnywhere)
		FKey InteractKey;

	UPROPERTY()
		UTimelineComponent* CooldownDoorTimeline;	

	UPROPERTY()
		UTimelineComponent* OpenDoorTimeline;

	UPROPERTY()
		UTimelineComponent* ResetDoorTimeline;
		*/

};
