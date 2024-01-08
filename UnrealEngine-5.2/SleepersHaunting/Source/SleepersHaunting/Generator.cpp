// Fill out your copyright notice in the Description page of Project Settings.


#include "Generator.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AGenerator::AGenerator(): powerSystemReference(nullptr)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGenerator::BeginPlay()
{
	Super::BeginPlay();
	powerSystemReference = Cast<APowerSystem>(UGameplayStatics::GetActorOfClass(GetWorld(), APowerSystem::StaticClass()));
}

// Called every frame
void AGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGenerator::EnergyGain()
{
	if (powerSystemReference)
	{
		if (bIsInCooldown == false)
		{
			bIsInCooldown = true;
			powerSystemReference->AddPower(energyFloat);
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, TEXT("Triggered -> +5 Power"));
		}
		else
		{
			GetWorldTimerManager().SetTimer(coolDownTimerHandle, this, &AGenerator::SetbIsInCooldownFalse, fCooldownTimer, false);
		}
	}
}

void AGenerator::SetbIsInCooldownFalse()
{
	bIsInCooldown = false;
}

