// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "A_SecurityMonitor.h"
#include "PlayerCharacter.h"

#include "A_SecuritySwitches.generated.h"

UCLASS()
class SLEEPERSHAUNTING_API AA_SecuritySwitches : public AActor
{
	GENERATED_BODY()

public:
	AA_SecuritySwitches();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Switch")
	bool IsLeftSwitch = true; // IF u want this to be a left switch which means (Previous camera)

public:
	UFUNCTION(BlueprintCallable, Category = "Switch")
	void ActivateSwitch();

	UPROPERTY(VisibleAnywhere);
	TObjectPtr<UStaticMeshComponent> SecuritySwitch;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Garage Handler")
	class AA_SecurityMonitor* FindSecurityCamera = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite);
	TObjectPtr<UBoxComponent> Collider;

	UPROPERTY()
	APlayerCharacter* ClosestCharacter = nullptr;

	UPROPERTY()
	TArray<APlayerCharacter*> Characters;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void GetClosestPlayer();
};

