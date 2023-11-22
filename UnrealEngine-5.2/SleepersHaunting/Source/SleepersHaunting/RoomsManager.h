// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoomsManager.generated.h"


USTRUCT(BlueprintType, Blueprintable)
struct FWaypointInfo //All Waypoints Info
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector WaypointPosition;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsOccupied;
};

USTRUCT(BlueprintType, Blueprintable)
struct FRoomInfo //All rooms info
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)//The current room ID
	int32 RoomID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)//To place which rooms are connected to the current room
	TArray<int32> ConnectedRooms;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)//Gets the Waypoint info and which waypoint they have.
	TArray<FWaypointInfo> WaypointsInfo;

};

UCLASS()
class SLEEPERSHAUNTING_API ARoomsManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoomsManager();

	//UFUNCTION(BlueprintCallable, Category = "Rooms")
	//TArray<FRoomInfo> GetRoomData() const { return RoomData; }

	//UFUNCTION(BlueprintCallable, Category = "Rooms")
	//void GetRoomsInfo(int32 RoomID) const;

	//Returns all connected rooms
	UFUNCTION(BlueprintCallable, Category = "Rooms")
	TArray<int32> GetConnectedRooms(int32 RoomID) const;

	// Returns the waypoints of the specified room
	UFUNCTION(BlueprintCallable, Category = "Rooms")
	TArray<FWaypointInfo> GetCurrentRoomWaypoints(int32 RoomID) const;

	// Returns a specific waypoint by index
	UFUNCTION(BlueprintCallable, Category = "Rooms")
	FWaypointInfo GetWaypointByIndex(int32 RoomID, int32 WaypointIndex) const;

	//Functions for the enemy
	// Debug connected rooms IDs for the specified room
	UFUNCTION(BlueprintCallable, Category = "Debug")
	void DebugConnectedRooms(int32 RoomID) const;

	// Debug waypoints for the specified room
	UFUNCTION(BlueprintCallable, Category = "Debug")
	void DebugWaypoints(int32 RoomID) const;

	// Debug a random connected room ID for the specified room
	UFUNCTION(BlueprintCallable, Category = "Debug")
	void DebugRandomConnectedRoomID(int32 RoomID) const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Rooms")
	TArray<FRoomInfo> RoomData;

	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Rooms")
		//TArray<FRoomInfo> RoomData;

};
