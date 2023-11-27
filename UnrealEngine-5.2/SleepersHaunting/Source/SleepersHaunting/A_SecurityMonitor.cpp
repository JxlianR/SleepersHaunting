// Fill out your copyright notice in the Description page of Project Settings.


#include "A_SecurityMonitor.h"

// Sets default values
AA_SecurityMonitor::AA_SecurityMonitor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AA_SecurityMonitor::BeginPlay()
{
	Super::BeginPlay();
	SetNumCameras();

}

void AA_SecurityMonitor::SetNumCameras()
{
	NumCameras = FMath::Min(CameraRenderTargets.Num(), CameraMaterials.Num());
}


void AA_SecurityMonitor::NextCamera()
{
	CurrentCameraIndex = (CurrentCameraIndex + 1) % NumCameras;
	UpdateMonitorView();
}

void AA_SecurityMonitor::PreviousCamera()
{
	CurrentCameraIndex = (CurrentCameraIndex - 1 + NumCameras) % NumCameras;
	UpdateMonitorView();
}

void AA_SecurityMonitor::UpdateMonitorView()
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



