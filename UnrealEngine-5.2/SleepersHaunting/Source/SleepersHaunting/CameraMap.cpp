// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraMap.h"

ACameraMap::ACameraMap()
{
	PrimaryActorTick.bCanEverTick = true;

	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
	RootComponent = CubeMesh;

	CurrentMaterialIndex = 0;

}

void ACameraMap::BeginPlay()
{
	Super::BeginPlay();
	// Initialize cube mesh (assuming you have a cube mesh asset)
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshAsset(TEXT("StaticMesh'/Game/Path/To/Your/CubeMesh.CubeMesh'"));
	if (CubeMeshAsset.Succeeded())
	{
		CubeMesh->SetStaticMesh(CubeMeshAsset.Object);
	}
	
	SetCubeMaterial();
	
}

// Called every frame
void ACameraMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACameraMap::NextMaterial()
{
	CurrentMaterialIndex = (CurrentMaterialIndex + 1) % MaterialArray.Num();
	SetCubeMaterial();
}

void ACameraMap::PreviousMaterial()
{
	CurrentMaterialIndex = (CurrentMaterialIndex - 1 + MaterialArray.Num()) % MaterialArray.Num();
	SetCubeMaterial();
}

void ACameraMap::SetCubeMaterial()
{
	if (MaterialArray.IsValidIndex(CurrentMaterialIndex) && CubeMesh)
	{
		UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(MaterialArray[CurrentMaterialIndex], this);
		if (DynamicMaterial)
		{
			CubeMesh->SetMaterial(0, DynamicMaterial);
		}
	}
}

