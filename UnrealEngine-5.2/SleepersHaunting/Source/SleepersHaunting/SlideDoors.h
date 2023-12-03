// SlideDoors.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SlideDoors.generated.h"

UCLASS()
class SLEEPERSHAUNTING_API ASlideDoors : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASlideDoors();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DoorVariables")
		bool lockedDoor;

	// Function to check if the door is locked
	UFUNCTION(BlueprintCallable, Category = "DoorFunctions")
		bool IsDoorLocked();

	// Function to set the door status to false (unlocked)
	UFUNCTION(BlueprintCallable, Category = "DoorFunctions")
		void SetDoorFalse();

	// Function to set the door status to true (locked)
	UFUNCTION(BlueprintCallable, Category = "DoorFunctions")
		void SetDoorTrue();

	
private:
	
};