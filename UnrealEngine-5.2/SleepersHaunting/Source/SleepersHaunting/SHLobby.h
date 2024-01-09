// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h" // Include for UCapsuleComponent
#include "TimerManager.h"
#include "Engine/PostProcessVolume.h"
#include "SHLobby.generated.h"

UCLASS()
class SLEEPERSHAUNTING_API ASHLobby : public AActor
{
	GENERATED_BODY()

public:
	ASHLobby();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay", Replicated)
		int32 CountPlayer = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay")
		float TimerDuration = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* LobbyMesh = nullptr;

	////////////////////////
	// Function to change material parameter
	void ChangeMaterialParameter();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PostProcessReference")
	APostProcessVolume* PostProcessVolume = nullptr;
	
private:
	FTimerHandle LobbyTimerHandle;

	UPROPERTY(EditAnywhere)
	FString MainLevelName = "";



	UFUNCTION(BlueprintCallable)
		void OnLobbyEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnLobbyExit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		void StartLobbyTimer();

	UFUNCTION()
		void StopLobbyTimer();

	UFUNCTION()
		void OpenNextLevel();
};
