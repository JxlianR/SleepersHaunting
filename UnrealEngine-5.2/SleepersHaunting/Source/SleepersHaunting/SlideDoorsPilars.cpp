// Fill out your copyright notice in the Description page of Project Settings.


#include "SlideDoorsPilars.h"

#include "PowerSystem.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ASlideDoorsPilars::ASlideDoorsPilars()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultScene"));
	RootComponent = DefaultSceneComponent;
	
	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolume"));
	TriggerVolume->SetupAttachment(DefaultSceneComponent);
	// TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &ASlideDoorsPilars::OnOverlapBegin);
	// TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &ASlideDoorsPilars::OnOverlapEnd);
}

// Called when the game starts or when spawned
void ASlideDoorsPilars::BeginPlay()
{
	Super::BeginPlay();
	powerSystemReference = Cast<APowerSystem>(UGameplayStatics::GetActorOfClass(GetWorld(), APowerSystem::StaticClass()));
}

// Called every frame
void ASlideDoorsPilars::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ASlideDoorsPilars::IsDoorLocked()
{
	return lockedDoor;
}

void ASlideDoorsPilars::SetDoorFalse()
{
	lockedDoor = false;
	if (powerSystemReference)
		powerSystemReference->DecreasePowerConsumption();
}

void ASlideDoorsPilars::SetDoorTrue()
{
	lockedDoor = true;
	if (powerSystemReference)
		powerSystemReference->IncreasePowerConsumption();
}

// void ASlideDoorsPilars::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
// {
// 	// Check if the overlapping actor is the SlideDoorMeshComponent
// 	if (OtherActor == AActor* )
// 	{
// 		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Triggered"));
// 		SetDoorTrue();
// 	}
// }
//
// void ASlideDoorsPilars::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
// {
// 	// Check if the overlapping actor is the SlideDoorMeshComponent
// 	if (OtherActor == )
// 	{
// 		// The SlideDoorMeshComponent has stopped overlapping with the TriggerVolume
// 		SetDoorFalse();
// 	}
// }

void ASlideDoorsPilars::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ASlideDoorsPilars, lockedDoor);

}
