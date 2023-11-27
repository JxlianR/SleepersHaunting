// Fill out your copyright notice in the Description page of Project Settings.


#include "A_SecurityCamera.h"
#include "Engine/Engine.h"

AA_SecurityCamera::AA_SecurityCamera()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AA_SecurityCamera::BeginPlay()
{
	Super::BeginPlay();
	SetNumCameras();
}

void AA_SecurityCamera::SetNumCameras()
{
	NumCameras = FMath::Min(CameraRenderTargets.Num(), CameraMaterials.Num());
}

void AA_SecurityCamera::NextCamera()
{
	CurrentCameraIndex = (CurrentCameraIndex + 1) % NumCameras;
	UpdateMonitorView();
}

void AA_SecurityCamera::PreviousCamera()
{
	CurrentCameraIndex = (CurrentCameraIndex - 1 + NumCameras) % NumCameras;
	UpdateMonitorView();
}

void AA_SecurityCamera::UpdateMonitorView()
{
	UStaticMeshComponent* MonitorScreenMesh = FindComponentByClass<UStaticMeshComponent>();
	if (MonitorScreenMesh)
	{
		UMaterialInstanceDynamic* MID = MonitorScreenMesh->CreateAndSetMaterialInstanceDynamic(0);
		if (MID)
		{
			MID->SetTextureParameterValue("CameraTexture", CameraRenderTargets[CurrentCameraIndex]);
		}
	}
}