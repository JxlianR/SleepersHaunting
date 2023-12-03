// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "GrabbableInterface.h"
#include "GameFramework/Actor.h"
#include "GrabbableObject.generated.h"

UCLASS()
class SLEEPERSHAUNTING_API AGrabbableObject : public AActor, public IGrabbableInterface
{
    GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* GrabbableMesh;
	
public:
    AGrabbableObject();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
    // Implement the interface functions
    virtual void GrabObject(ACharacter* PlayerCharacter) override;
    virtual void ReleaseObject() override;
};