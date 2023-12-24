// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"
#include "SHLobby.generated.h"

UCLASS()
class SLEEPERSHAUNTING_API ASHLobby : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASHLobby();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	
private:
	FTimerHandle LobbyTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay", meta = (AllowPrivateAccess = "true", Replicated))
		int32 CountPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay", meta = (AllowPrivateAccess = "true"))
		float TimerDuration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UBoxComponent* LobbyBox;

	UFUNCTION()
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
