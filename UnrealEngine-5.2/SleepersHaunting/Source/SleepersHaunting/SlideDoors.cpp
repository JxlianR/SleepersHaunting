// Fill out your copyright notice in the Description page of Project Settings.


#include "SlideDoors.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ASlideDoors::ASlideDoors()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	lockedDoor = false;
}

// Called when the game starts or when spawned
void ASlideDoors::BeginPlay()
{
	Super::BeginPlay();
	powerSystemReference = Cast<APowerSystem>(UGameplayStatics::GetActorOfClass(GetWorld(), APowerSystem::StaticClass()));

}

// Called every frame
void ASlideDoors::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ASlideDoors::IsDoorLocked()
{
	return lockedDoor;
}

void ASlideDoors::SetDoorFalse()
{
	lockedDoor = false;

	FVector NewLocation = GetActorLocation();
	NewLocation.X -= 130.0f;
	SetActorLocation(NewLocation);

	if (powerSystemReference)
		powerSystemReference->DecreasePowerConsumption();
}

void ASlideDoors::SetDoorTrue()
{
	lockedDoor = true;

	FVector NewLocation = GetActorLocation();
	NewLocation.X += 130.0f;
	SetActorLocation(NewLocation);

	if (powerSystemReference)
		powerSystemReference->IncreasePowerConsumption();
}

