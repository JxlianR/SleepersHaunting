// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "JumpableInterface.h"
#include "Roomba.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttachedToPlayer);

UCLASS()
class SLEEPERSHAUNTING_API ARoomba : public AActor, public IJumpableInterface
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

	void  GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	FOnAttachedToPlayer OnRoombaAttachedEvent;

	UFUNCTION()
	void TriggerRoombaAttachedEvent();

	virtual void JumpedOn_Implementation() override;

protected:
	UFUNCTION(Client, Reliable)
	void ChangeActiveState(bool active);

	UFUNCTION(Client, Reliable)
	void GetClosestPlayer();

	UFUNCTION(Client, Reliable)
	void FollowPlayer(float DeltaTime);

	UFUNCTION(Client, Reliable)
	void AttachToPlayer(APlayerCharacter* Player);

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(Client, Reliable)
	void OnOverlapFunction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
protected:
	UPROPERTY(VisibleAnywhere);
	TObjectPtr<USceneComponent> DefaultSceneRoot;
	
	UPROPERTY(VisibleAnywhere);
	TObjectPtr<UStaticMeshComponent> Roomba;

	UPROPERTY(VisibleAnywhere);
	TObjectPtr<USphereComponent> Collider;

	UPROPERTY(Replicated)
	FVector StartLocation;

	UPROPERTY()
	FRotator StartRotation;
	
	UPROPERTY(EditAnywhere)
	float Speed = 1.0f;

	UPROPERTY(EditAnywhere)
	float InitialLifetime = 10.0f;

	UPROPERTY(EditAnywhere)
	float InitialTimerToActivate = 10.0f;

	UPROPERTY(Replicated, VisibleAnywhere)
	APlayerCharacter* ClosestCharacter;

	UPROPERTY(Replicated)
	APlayerCharacter* AttachedCharacter;

	UPROPERTY(Replicated)
	float ShortestDistance;

	UPROPERTY(VisibleAnywhere, Replicated)
	TArray<APlayerCharacter*> Characters;

private:
	bool Active = true;
	
	bool Attached;

	float Lifetime = InitialLifetime;

	float TimerToActivate = InitialTimerToActivate;
};
