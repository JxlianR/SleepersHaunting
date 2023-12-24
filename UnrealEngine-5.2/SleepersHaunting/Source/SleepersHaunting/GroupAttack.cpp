// Fill out your copyright notice in the Description page of Project Settings.


#include "GroupAttack.h"
#include "Kismet/GameplayStatics.h"

//Classes
#include "TheTwins.h"
#include "MyGameState.h"



// Sets default values
AGroupAttack::AGroupAttack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	LeftTwinAtk = false;
	RightTwinAtk = false;
}

// Called when the game starts or when spawned
void AGroupAttack::BeginPlay()
{
	Super::BeginPlay();
	GetAllInstanceClasses();
}

// Called every frame
void AGroupAttack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGroupAttack::AttemptGroupAttack(bool whichTwin)
{
	if (whichTwin) {
		LeftTwinAtk = true;
	}
	else {
		RightTwinAtk = true;
	}

	if (LeftTwinAtk && RightTwinAtk) {
		TheTwinsInstance_1->PauseAllTwinTimers();
		TheTwinsInstance_2->PauseAllTwinTimers();
		GetWorldTimerManager().SetTimer(SAttackTimerHandle, this, &AGroupAttack::TryGroupAttack, SattackTimer, false);
	}
}

void AGroupAttack::LeaveAttemptGroupAttack(bool whichTwin)
{
	if (whichTwin) {
		LeftTwinAtk = false;
	}
	else {
		RightTwinAtk = false;
	}
}

void AGroupAttack::TryGroupAttack()
{
	LeftTwinAtk = false;
	RightTwinAtk = false;
	bool isLeftDoorLocked = TheTwinsInstance_1->ReturnLockedDoor();
	bool isRightDoorLocked = TheTwinsInstance_2->ReturnLockedDoor();

	if (!isLeftDoorLocked || !isRightDoorLocked) {
		AMyGameStateInstance->SetLoseCondition(1);
	}
	else
	{
		TheTwinsInstance_1->FailedAttack();
		TheTwinsInstance_2->FailedAttack();
	}
}

// Add this function to cancel the timer if needed
void AGroupAttack::CancelGroupAttackTimer()
{
	if (GetWorldTimerManager().IsTimerActive(SAttackTimerHandle)) {
		GetWorldTimerManager().ClearTimer(SAttackTimerHandle);
	}
}

void AGroupAttack::GetAllInstanceClasses()
{
	if (AMyGameState* GameState = Cast<AMyGameState>(UGameplayStatics::GetGameState(GetWorld())))
	{
		AMyGameStateInstance = GameState;
	}
	else if (!AMyGameStateInstance)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Game State Instance not found!"));
	}
}
