// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "GrabbableInterface.h"
#include "GameFramework/Actor.h"
#include "GrabbableObject.generated.h"

class UMeshComponent;

UCLASS()
class SLEEPERSHAUNTING_API AGrabbableObject : public AActor, public IGrabbableInterface
{
    GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* GrabbableMesh;
	
	
public:
	AGrabbableObject();

	virtual void BeginPlay() override;

	virtual void Grab_Implementation() override;
};