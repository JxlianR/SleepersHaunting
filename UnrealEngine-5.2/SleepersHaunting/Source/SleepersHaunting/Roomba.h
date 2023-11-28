// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "Roomba.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttachedToPlayer);

UCLASS()
class SLEEPERSHAUNTING_API ARoomba : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoomba();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FOnAttachedToPlayer OnRoombaAttachedEvent;

	UFUNCTION()
	void TriggerRoombaAttachedEvent();

protected:
	UFUNCTION()
	void ChangeActiveState(bool active);

	UFUNCTION()
	void GetClosestPlayer();

	UFUNCTION()
	void FollowPlayer(float DeltaTime);

	UFUNCTION()
	void AttachToPlayer(APlayerCharacter* Player);

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
protected:
	UPROPERTY(VisibleAnywhere);
	TObjectPtr<USceneComponent> DefaultSceneRoot;
	
	UPROPERTY(VisibleAnywhere);
	TObjectPtr<UStaticMeshComponent> Roomba;

	UPROPERTY(VisibleAnywhere);
	TObjectPtr<USphereComponent> Collider;

	UPROPERTY()
	FVector StartLocation;

	UPROPERTY()
	FRotator StartRotation;
	
	UPROPERTY(EditAnywhere)
	float Speed = 1.0f;

	UPROPERTY(EditAnywhere)
	float InitialLifetime = 10.0f;

	UPROPERTY(EditAnywhere)
	float InitialTimerToActivate = 10.0f;

	UPROPERTY()
	APlayerCharacter* ClosestCharacter;

	UPROPERTY()
	TArray<APlayerCharacter*> Characters;

private:
	bool Active = true;
	
	bool Attached;

	float Lifetime = InitialLifetime;

	float TimerToActivate = InitialTimerToActivate;

	
	

};
