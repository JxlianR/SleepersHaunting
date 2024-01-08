// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "PowerSystem.h"

#include "Generator.generated.h"

UCLASS()
class SLEEPERSHAUNTING_API AGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Function to set the door status to true (locked)
	UFUNCTION(BlueprintCallable, Category = "Energy")
	void EnergyGain();

	UPROPERTY(BlueprintReadWrite)
	float energyFloat = 5.0f;
	
private:
	APowerSystem* powerSystemReference;
};
