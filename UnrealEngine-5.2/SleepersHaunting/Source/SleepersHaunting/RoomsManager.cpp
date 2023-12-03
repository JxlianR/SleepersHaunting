#include "RoomsManager.h"

// Sets default values
ARoomsManager::ARoomsManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARoomsManager::BeginPlay()
{
	Super::BeginPlay();
	DebugRandomConnectedRoomID(3);

}

// Called every frame
void ARoomsManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TArray<int32> ARoomsManager::GetConnectedRooms(int32 RoomID) const
{
	TArray<int32> ConnectedRooms;

	// Find the room with the specified ID
	//Theres is a pointer here
	const FRoomInfo* CurrentRoom = nullptr;
	for (const FRoomInfo& Room : RoomData)
	{
		if (Room.RoomID == RoomID)
		{
			CurrentRoom = &Room;
			break;
		}
	}

	// If the room is found, add connected rooms to the result array
	if (CurrentRoom)
	{
		ConnectedRooms.Append(CurrentRoom->ConnectedRooms);
	}

	return ConnectedRooms;
}

TArray<FWaypointInfo> ARoomsManager::GetCurrentRoomWaypoints(int32 RoomID) const
{
	TArray<FWaypointInfo> CurrentRoomWaypoints;

	// Find the room with the specified ID
	const FRoomInfo* CurrentRoom = nullptr;
	for (const FRoomInfo& Room : RoomData)
	{
		if (Room.RoomID == RoomID)
		{
			CurrentRoom = &Room;
			break;
		}
	}

	// If the room is found, copy the waypoints to the result array
	if (CurrentRoom)
	{
		CurrentRoomWaypoints = CurrentRoom->WaypointsInfo;
	}

	return CurrentRoomWaypoints;
}

FWaypointInfo ARoomsManager::GetWaypointByIndex(int32 RoomID, int32 WaypointIndex) const
{
	// Get waypoints of the specified room
	TArray<FWaypointInfo> RoomWaypoints = GetCurrentRoomWaypoints(RoomID);

	// Check if the index is valid
	if (WaypointIndex >= 0 && WaypointIndex < RoomWaypoints.Num())
	{
		// Return the waypoint at the specified index
		return RoomWaypoints[WaypointIndex];
	}
	else
	{
		// Log a warning if the index is out of bounds
		FString Message = FString::Printf(TEXT("Invalid waypoint index for room ID %d: %d"), RoomID, WaypointIndex);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, Message);
		return FWaypointInfo(); // Return a default-constructed FWaypointInfo
	}
}

/*
TArray<FRoomInfo> ARoomsManager::GetRoomData() const
{
	return RoomData;
}
*/

/*
void ARoomsManager::GetRoomsInfo(int32 RoomID) const
{

	// Find the room with the specified ID
	const FRoomInfo* CurrentRoom = nullptr;
	for (const FRoomInfo& Room : RoomData)
	{
		if (Room.RoomID == RoomID)
		{
			CurrentRoom = &Room;
			break;
		}
	}

	// If the room is found, print information about it
	if (CurrentRoom)
	{
		UE_LOG(LogTemp, Warning, TEXT("Room ID: %d"), CurrentRoom->RoomID);

		UE_LOG(LogTemp, Warning, TEXT("Connected Rooms:"));
		for (int32 ConnectedRoomID : CurrentRoom->ConnectedRooms)
		{
			UE_LOG(LogTemp, Warning, TEXT("%d"), ConnectedRoomID);
		}

		UE_LOG(LogTemp, Warning, TEXT("Waypoints Info:"));
		int32 WaypointIndex = 0;
		for (const FWaypointInfo& Waypoint : CurrentRoom->WaypointsInfo)
		{
			UE_LOG(LogTemp, Warning, TEXT("Waypoint %d - Position: %s, Is Occupied: %s"),
				WaypointIndex,
				*Waypoint.WaypointPosition.ToString(),
				Waypoint.IsOccupied ? TEXT("True") : TEXT("False"));

			WaypointIndex++;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Room not found with ID: %d"), RoomID);
	}

}
*/


//Debugs
void ARoomsManager::DebugConnectedRooms(int32 RoomID) const
{
	TArray<int32> ConnectedRooms = GetConnectedRooms(RoomID);

	FString Message = FString::Printf(TEXT("Connected Rooms for Room %d:"), RoomID);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, Message);

	for (int32 ConnectedRoomID : ConnectedRooms)
	{
		Message = FString::Printf(TEXT("%d"), ConnectedRoomID);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, Message);

	}
}

void ARoomsManager::DebugWaypoints(int32 RoomID) const
{
	TArray<FWaypointInfo> Waypoints = GetCurrentRoomWaypoints(RoomID);

	FString Message = FString::Printf(TEXT("Waypoints for Room %d:"), RoomID);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, Message);

	for (int32 Index = 0; Index < Waypoints.Num(); ++Index)
	{
		const FWaypointInfo& Waypoint = Waypoints[Index];
		Message = FString::Printf(TEXT("Waypoint %d - Is Occupied: %s"), Index, Waypoint.IsOccupied ? TEXT("True") : TEXT("False"));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, Message);

	}
}

void ARoomsManager::DebugRandomConnectedRoomID(int32 RoomID) const
{
	TArray<int32> ConnectedRooms = GetConnectedRooms(RoomID);

	if (ConnectedRooms.Num() > 0)
	{
		// Get a random index within the range of connected rooms
		int32 RandomIndex = FMath::RandRange(0, ConnectedRooms.Num() - 1);

		// Get the random connected room ID
		int32 RandomConnectedRoomID = ConnectedRooms[RandomIndex];

		FString Message = FString::Printf(TEXT("Random Connected Room ID for Room %d: %d"), RoomID, RandomConnectedRoomID);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, Message);
	}
	else
	{
		FString Message = FString::Printf(TEXT("Room %d has no connected rooms."), RoomID);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, Message);
	}
}




//Important functions for the Twins
int32 ARoomsManager::GetRandomConnectedRoomID(int32 RoomID) const
{
	TArray<int32> ConnectedRooms = GetConnectedRooms(RoomID);

	if (ConnectedRooms.Num() > 0)
	{
		// Get a random index within the range of connected rooms
		int32 RandomIndex = FMath::RandRange(0, ConnectedRooms.Num() - 1);

		// Return the random connected room ID
		return ConnectedRooms[RandomIndex];
	}
	else
	{
		// Log a warning if the room has no connected rooms
		UE_LOG(LogTemp, Warning, TEXT("Room %d has no connected rooms."), RoomID);
		return -1; // You can choose a suitable default value for no connected rooms
	}
}

FVector ARoomsManager::GetSpecificWaypoint(int32 RoomID, bool bUseFirstWaypoint) const
{
	TArray<FWaypointInfo> Waypoints = GetCurrentRoomWaypoints(RoomID);

	if (Waypoints.Num() > 0)
	{
		// Get the index based on the boolean parameter
		int32 WaypointIndex = bUseFirstWaypoint ? 0 : 1;

		if (WaypointIndex >= 0 && WaypointIndex < Waypoints.Num())
		{
			return Waypoints[WaypointIndex].WaypointPosition;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Invalid waypoint index for room ID %d: %d"), RoomID, WaypointIndex);
			return FVector::ZeroVector; // You can choose a suitable default value
		}
	}
	else
	{
		// Log a warning if the room has no waypoints
		return FVector::ZeroVector; // You can choose a suitable default value
	}
}
