#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Net/UnrealNetwork.h"



#include "TheTwins.generated.h"

UCLASS()
class SLEEPERSHAUNTING_API ATheTwins : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATheTwins();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Twins")
		bool IsLeftSided;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "Twins")
		bool CanAttack;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Twins")
		TArray<int32> AccessRooms;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Twins")
		int32 AttackRoom;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Twins", ReplicatedUsing = MoveTwinToWaypoint)
		int32 CurrentRoomID;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Twins")
		USkeletalMeshComponent* TwinMesh;

	// Duration for movement cooldown
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Twins")
		float CDmovementDuration;
	// Duration for special attack cooldown
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Twins")
		float SattackDuration;
	// Duration for attack cooldown
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Twins")
		float CDattackDuration;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Twins")
		float SsuccessDuration;


	// Function to move the twin to a random connected room
	UFUNCTION(BlueprintCallable, Category = "Twins")
		void MoveToRandomConnectedRoom();
	// Function to move the twin to a specific waypoint
	UFUNCTION(BlueprintCallable, Category = "Twins")
		void MoveTwinToWaypoint();
	// Function to update the current room ID
	UFUNCTION(BlueprintCallable, Category = "Twins")
		void UpdateCurrentRoomID(int32 NewRoomID);
	UFUNCTION(BlueprintCallable, Category = "Twins")
		void TwinAttack();
	UFUNCTION(BlueprintCallable, Category = "Twins")
		void SuccessAttack();
	UFUNCTION(BlueprintCallable, Category = "Twins")
		void FailedAttack();
	UFUNCTION(BlueprintCallable, Category = "Twins")
		void EnableAttack();
	UFUNCTION(BlueprintCallable, Category = "Twins")
		void PauseAllTwinTimers();
	UFUNCTION(BlueprintCallable, Category = "Twins")
		void ResumeAllTwinTimers();
	UFUNCTION(BlueprintCallable, Category = "Twins")
		void ForceGroupATK();
	UFUNCTION(BlueprintCallable, Category = "Twins")
		bool ReturnLockedDoor();
	
	
	//Classes
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Twins")
		class ARoomsManager* RoomsManagerInstance;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Twins")
		class ASlideDoors* SlideDoorsInstance;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Twins")
		class AGroupAttack* GroupAttackInstance;


	class AMyGameState* AMyGameStateInstance;

private:

	UWorld* World;

	UFUNCTION()
		void GetAllInstanceClasses();

	// Timer handles for managing cooldowns
	FTimerHandle CDMovementTimerHandle;
	FTimerHandle SAttackTimerHandle;
	FTimerHandle CDAttackTimerHandle;
	FTimerHandle SuccessAttackTimerHandle;

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

};