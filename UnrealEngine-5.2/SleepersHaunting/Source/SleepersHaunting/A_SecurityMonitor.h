// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Components/StaticMeshComponent.h"
#include "A_SecurityMonitor.generated.h"

UCLASS()
class SLEEPERSHAUNTING_API AA_SecurityMonitor : public AActor
{
	GENERATED_BODY()
	
public:
	AA_SecurityMonitor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Audio")
		class USoundCue* MonitorSoundCue = nullptr;
public:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UPROPERTY(EditAnywhere, Category = "Camera")
		TArray<UTextureRenderTarget2D*> CameraRenderTargets;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", ReplicatedUsing = UpdateMonitorView)
		int32 CurrentCameraIndex;

	UFUNCTION(BlueprintCallable, Category = "Camera")
		void NextCamera();

	UFUNCTION(BlueprintCallable, Category = "Camera")
		void PreviousCamera();

	UFUNCTION(BlueprintCallable, Category = "Camera")
		void UpdateMonitorView();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
		class ACameraMap* CameraMapInstance1;

	UFUNCTION(BlueprintCallable, Category = "Audio")
		void PlayMonitorSound();
private:
	UPROPERTY(EditAnywhere, Category = "Camera")
		TArray<UMaterialInterface*> CameraMaterials;

	int32 NumCameras = 0; // Automatically set during BeginPlay

	UFUNCTION()
		void SetNumCameras();
};