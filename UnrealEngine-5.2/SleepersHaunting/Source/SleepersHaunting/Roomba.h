// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "Roomba.generated.h"

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

protected:
	UFUNCTION()
	void ChangeActiveState(bool active);

	UFUNCTION()
	void GetClosestPlayer();

	UFUNCTION()
	void FollowPlayer();
	
protected:
	UPROPERTY(VisibleAnywhere);
	TObjectPtr<USceneComponent> DefaultSceneRoot;
	
	UPROPERTY(VisibleAnywhere);
	TObjectPtr<UStaticMeshComponent> Roomba;

	UPROPERTY(VisibleAnywhere);
	TObjectPtr<USphereComponent> Collider;

	UPROPERTY(EditAnywhere)
	FVector StartLocation;
	
	UPROPERTY(EditAnywhere)
	float Speed = 1.0f;

	UPROPERTY(EditAnywhere)
	float Lifetime = 30.0f;

	UPROPERTY()
	APlayerCharacter* ClosestCharacter;

	UPROPERTY()
	TArray<APlayerCharacter*> Characters;
	
	bool Active;

	
	

};
