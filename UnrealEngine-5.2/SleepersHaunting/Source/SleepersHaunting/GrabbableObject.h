// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GrabbableInterface.h"
#include "GameFramework/Actor.h"
#include "GrabbableObject.generated.h"

UCLASS()
class SLEEPERSHAUNTING_API AGrabbableObject : public AActor, public IGrabbableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrabbableObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Grab_Implementation(AActor* Actor) override;
};
