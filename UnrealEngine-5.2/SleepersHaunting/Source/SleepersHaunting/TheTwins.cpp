// Fill out your copyright notice in the Description page of Project Settings.


#include "TheTwins.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ATheTwins::ATheTwins()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Default values
	CurrentRoomID = 1;
	AttackRoom = 0;
	IsLeftSided = true;
	CanAttack = true;
}

// Called when the game starts or when spawned
void ATheTwins::BeginPlay()
{
	Super::BeginPlay();
	TwinMesh = FindComponentByClass<USkeletalMeshComponent>();
	MoveTwinToWaypoint();
	GetWorldTimerManager().SetTimer(CDMovementTimerHandle, this, &ATheTwins::MoveToRandomConnectedRoom, CDmovementDuration, false);
}

// Called every frame
void ATheTwins::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATheTwins::UpdateCurrentRoomID(int32 NewRoomID)
{
	CurrentRoomID = NewRoomID;
	// Display the current room ID on screen
	if (IsLeftSided) {
		//qFString Message = FString::Printf(TEXT("Left Twin is in Room %d"), CurrentRoomID);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, Message);
	}
	else if (!IsLeftSided) {
		//FString Message = FString::Printf(TEXT("Right Twin is in Room %d"), CurrentRoomID);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, Message);
	}
}

void ATheTwins::MoveTwinToWaypoint()
{
	if (RoomsManagerInstance)
	{
		// Get the waypoint position from the RoomsManager
		FVector WaypointLocation = RoomsManagerInstance->GetSpecificWaypoint(CurrentRoomID, IsLeftSided);
		// Update the mesh component's location to the waypoint
		if (TwinMesh)
		{
			TwinMesh->SetWorldLocation(WaypointLocation);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "TwinMesh is not valid");
		}
	}
	else
	{
		// RoomsManager doesn't exist
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "RoomsManager instance is not valid");
	}
}

void ATheTwins::MoveToRandomConnectedRoom()
{
	if (RoomsManagerInstance)
	{
		// Get the connected rooms for the current room
		TArray<int32> ConnectedRooms = RoomsManagerInstance->GetConnectedRooms(CurrentRoomID);

		// Filter the connected rooms based on access
		TArray<int32> AccessibleRooms;
		for (int32 ConnectedRoomID : ConnectedRooms)
		{
			if (AccessRooms.Contains(ConnectedRoomID))
			{
				if (!(ConnectedRoomID == AttackRoom && !CanAttack))
				{
					AccessibleRooms.Add(ConnectedRoomID);
				}
			}
		}

		// If there are accessible rooms, choose one randomly
		if (AccessibleRooms.Num() > 0)
		{
			int32 RandomIndex = FMath::RandRange(0, AccessibleRooms.Num() - 1);
			int32 NextRoomID = AccessibleRooms[RandomIndex];

			// Update the current room ID
			UpdateCurrentRoomID(NextRoomID);
			// Move the twin to the chosen waypoint of the new room
			MoveTwinToWaypoint();

			// Check if the current room is the attack room
			if (CurrentRoomID == AttackRoom)
			{
				// Start the special attack timer
				GetWorldTimerManager().SetTimer(SAttackTimerHandle, this, &ATheTwins::TwinAttack, SattackDuration, false);
			}
			else
			{
				// Start the movement timer for the next random room
				GetWorldTimerManager().SetTimer(CDMovementTimerHandle, this, &ATheTwins::MoveToRandomConnectedRoom, CDmovementDuration, false);
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "The twin has no accessible connected rooms.");
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "RoomsManager instance is not valid");
	}
}

void ATheTwins::TwinAttack()
{
	if (SlideDoorsInstance)
	{
		// Check if the door is locked
		bool IsDoorLocked = SlideDoorsInstance->IsDoorLocked();

		if (IsDoorLocked)
		{
			MoveToRandomConnectedRoom();
			// Start the cooldown timer
			GetWorldTimerManager().SetTimer(CDAttackTimerHandle, this, &ATheTwins::EnableAttack, CDattackDuration, false);
			CanAttack = false;
		}
		else
		{
			//Player losing condition
			UGameplayStatics::OpenLevel(GetWorld(), FName("GameOverMenu"));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Player lost!"));
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "SlideDoors instance is not valid");
	}
}

void ATheTwins::PauseAllTwinTimers()
{
	// Pause the movement timer if it's active
	if (GetWorldTimerManager().IsTimerActive(CDMovementTimerHandle))
	{
		GetWorldTimerManager().PauseTimer(CDMovementTimerHandle);
	}

	// Pause the special attack timer if it's active
	if (GetWorldTimerManager().IsTimerActive(SAttackTimerHandle))
	{
		GetWorldTimerManager().PauseTimer(SAttackTimerHandle);
	}

	// Pause the attack timer if it's active
	if (GetWorldTimerManager().IsTimerActive(CDAttackTimerHandle))
	{
		GetWorldTimerManager().PauseTimer(CDAttackTimerHandle);
	}
}

void ATheTwins::ResumeAllTwinTimers()
{
	// Resume the movement timer if it was active
	if (GetWorldTimerManager().IsTimerPaused(CDMovementTimerHandle))
	{
		GetWorldTimerManager().UnPauseTimer(CDMovementTimerHandle);
	}

	// Resume the special attack timer if it was active
	if (GetWorldTimerManager().IsTimerPaused(SAttackTimerHandle))
	{
		GetWorldTimerManager().UnPauseTimer(SAttackTimerHandle);
	}

	// Resume the attack timer if it was active
	if (GetWorldTimerManager().IsTimerPaused(CDAttackTimerHandle))
	{
		GetWorldTimerManager().UnPauseTimer(CDAttackTimerHandle);
	}
}

void ATheTwins::EnableAttack()
{
	CanAttack = true;
}