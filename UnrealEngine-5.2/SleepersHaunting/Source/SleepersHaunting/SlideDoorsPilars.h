// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SlideDoorsPilars.generated.h"

class UBoxComponent;
class APowerSystem;

UCLASS()
class SLEEPERSHAUNTING_API ASlideDoorsPilars : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASlideDoorsPilars();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "DoorVariables")
	bool lockedDoor;

	// Function to check if the door is locked
	UFUNCTION(BlueprintCallable, Category = "DoorFunctions")
	bool IsDoorLocked();

	// Function to set the door status to false (unlocked)
	UFUNCTION(BlueprintCallable, Category = "DoorFunctions")
	void SetDoorFalse();

	// Function to set the door status to true (locked)
	UFUNCTION(BlueprintCallable, Category = "DoorFunctions")
	void SetDoorTrue();

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* DefaultSceneComponent;
	
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* TriggerVolume;
	
	// UFUNCTION()
	// void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//
	// UFUNCTION()
	// void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	APowerSystem* powerSystemReference;

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;
};
