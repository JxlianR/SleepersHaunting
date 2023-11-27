// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Components/StaticMeshComponent.h"

#include "A_SecurityCamera.generated.h"

UCLASS()
class SLEEPERSHAUNTING_API AA_SecurityCamera : public AActor
{
	GENERATED_BODY()

public:
	AA_SecurityCamera();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Camera")
		TArray<UTextureRenderTarget2D*> CameraRenderTargets;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		int32 CurrentCameraIndex = 0;

	UFUNCTION(BlueprintCallable, Category = "Camera")
		void NextCamera();

	UFUNCTION(BlueprintCallable, Category = "Camera")
		void PreviousCamera();

	UFUNCTION(BlueprintCallable, Category = "Camera")
		void UpdateMonitorView();

private:
	UPROPERTY(EditAnywhere, Category = "Camera")
		TArray<UMaterialInterface*> CameraMaterials;

	int32 NumCameras = 0; // Automatically set during BeginPlay

	UFUNCTION()
		void SetNumCameras();
};