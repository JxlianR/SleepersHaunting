// Fill out your copyright notice in the Description page of Project Settings.


#include "A_SecurityMonitor.h"
#include "CameraMap.h"

#include "Net/UnrealNetwork.h"

// Sets default values
AA_SecurityMonitor::AA_SecurityMonitor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CurrentCameraIndex = 0;
}

// Called when the game starts or when spawned
void AA_SecurityMonitor::BeginPlay()
{
	Super::BeginPlay();
	SetNumCameras();
}

void AA_SecurityMonitor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(AA_SecurityMonitor, CurrentCameraIndex);
}

void AA_SecurityMonitor::SetNumCameras()
{
	NumCameras = FMath::Min(CameraRenderTargets.Num(), CameraMaterials.Num());
}

void AA_SecurityMonitor::NextCamera()
{
	CurrentCameraIndex = (CurrentCameraIndex + 1) % NumCameras;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("CurrentCameraIndex: %d"), CurrentCameraIndex));
	UpdateMonitorView();
	if (CameraMapInstance1) {
		CameraMapInstance1->NextMaterial();
	}
}

void AA_SecurityMonitor::PreviousCamera()
{
	CurrentCameraIndex = (CurrentCameraIndex - 1 + NumCameras) % NumCameras;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("CurrentCameraIndex: %d"), CurrentCameraIndex));
	UpdateMonitorView();
	if (CameraMapInstance1) {
		CameraMapInstance1->PreviousMaterial();
	}
}

void AA_SecurityMonitor::UpdateMonitorView()
{
	UStaticMeshComponent* MonitorScreenMesh = FindComponentByClass<UStaticMeshComponent>();
	UWorld* World = GetWorld();
	if (World->IsClient())
		int CamIndex = CurrentCameraIndex;
	
	if (MonitorScreenMesh)
	{
		if (CurrentCameraIndex >= 0 && CurrentCameraIndex < CameraMaterials.Num())
		{
			UMaterialInterface* NewMaterial = CameraMaterials[CurrentCameraIndex];
			// Set the new material
			MonitorScreenMesh->SetMaterial(0, NewMaterial);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Changed Camera"));
		}
	}
}
