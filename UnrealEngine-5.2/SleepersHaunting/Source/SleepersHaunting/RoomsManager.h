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
		FVector WaypointPosition = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool IsOccupied = false;
};

USTRUCT(BlueprintType, Blueprintable)
struct FRoomInfo //All rooms info
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadOnly)//The current room ID
		int32 RoomID = 1;

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
	UFUNCTION(BlueprintCallable, Category = "Debug")
		void DebugConnectedRooms(int32 RoomID) const;
	UFUNCTION(BlueprintCallable, Category = "Debug")
		void DebugWaypoints(int32 RoomID) const;
	UFUNCTION(BlueprintCallable, Category = "Debug")
		void DebugRandomConnectedRoomID(int32 RoomID) const;


	UFUNCTION(BlueprintCallable, Category = "Rooms")
		int32 GetRandomConnectedRoomID(int32 RoomID) const;
	UFUNCTION(BlueprintCallable, Category = "Rooms")
		FVector GetSpecificWaypoint(int32 RoomID, bool bUseFirstWaypoint) const;

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
