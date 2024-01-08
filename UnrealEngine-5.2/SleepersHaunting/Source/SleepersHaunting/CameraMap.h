// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInterface.h"  // Include for UMaterialInterface
#include "Materials/MaterialInstanceDynamic.h"
#include "CameraMap.generated.h"
UCLASS()
class SLEEPERSHAUNTING_API ACameraMap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraMap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Array to store textures
	UPROPERTY(EditAnywhere, Category = "Material")
		TArray<UMaterialInterface*> MaterialArray;

	// Function to switch to the next material
	UFUNCTION(BlueprintCallable, Category = "Material")
		void NextMaterial();

	// Function to switch to the previous material
	UFUNCTION(BlueprintCallable, Category = "MAterial")
		void PreviousMaterial();

private:
	// Index of the current material
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = SetCubeMaterial)
	int32 CurrentMaterialIndex = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cube", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* CubeMesh = nullptr;

	// Function to set the cube's texture based on the current index
	UFUNCTION()
	void SetCubeMaterial();

};
