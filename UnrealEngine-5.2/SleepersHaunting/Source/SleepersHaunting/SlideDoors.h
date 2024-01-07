#pragma once

#include "CoreMinimal.h"
#include "GrabbableInterface.h"
#include "GameFramework/Actor.h"
#include "PowerSystem.h"
#include "Net/UnrealNetwork.h"
#include "SlideDoors.generated.h"

class UBoxComponent;

UCLASS()
class SLEEPERSHAUNTING_API ASlideDoors : public AActor, public IGrabbableInterface
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
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "DoorVariables")
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

	virtual void Grab_Implementation() override;
	virtual void Release_Implementation() override;
	
	void SmoothMoveToInitialLocation(float DeltaTime);
	void GrabTick(float DeltaTime);
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MainMeshComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* SlideDoorMeshComponent;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* TriggerVolume;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsBeingGrabbed;
	
private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere);
	bool bShouldMoveSmoothly;

	APowerSystem* powerSystemReference;

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;
};