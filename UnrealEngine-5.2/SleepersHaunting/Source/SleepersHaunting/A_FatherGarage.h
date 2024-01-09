#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerState.h"
#include "Net/UnrealNetwork.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TimelineComponent.h"


#include "A_FatherGarage.generated.h"

UCLASS()
class SLEEPERSHAUNTING_API AA_FatherGarage : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AA_FatherGarage();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Audio")
	class USoundCue* GarageSoundCue = nullptr;

public:
    
	UFUNCTION()
    void SetHandler1(bool NewValue);
	UFUNCTION()
    void SetHandler2(bool NewValue);

	//SetMulticast is something it should be executed in all clients when the server calls this function.
    UFUNCTION(BlueprintCallable)
    void SetLosingConditionTrue();

    UFUNCTION()
    void StartCooldownTimer();

    UFUNCTION()
    void StartOpenDoorTimeline();

    UFUNCTION()
    void OnOpenDoorTimelineCompleted();

    UFUNCTION()
    void StartResetTimeline();

	UFUNCTION()
	void StopCooldownTimer();

	UFUNCTION()
	void StopOpenDoorTimeline();

	UFUNCTION()
	void StopResetTimeline();

	UFUNCTION()
	void StopAllTimers();

	UFUNCTION(BlueprintCallable, Category = "Audio")
		void PlayGarageSound();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    bool bLosingCondition = false;

    UPROPERTY(Replicatedusing = StartResetTimeline, BlueprintReadOnly)
    bool bHandler1 = false;

    UPROPERTY(ReplicatedUsing = StartResetTimeline, BlueprintReadOnly)
    bool bHandler2 = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UStaticMeshComponent* GarageDoorMesh = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float ZOffset = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float OpenDoorDuration = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float ResetDoorDuration = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float CooldownDuration = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
    UCurveFloat* OpenDoorCurve = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
    UCurveFloat* ResetDoorCurve = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UTimelineComponent* OpenDoorTimeline = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UTimelineComponent* ResetDoorTimeline = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UTimelineComponent* CooldownDoorTimeline = nullptr;

	UPROPERTY()
	class AMyGameState* AMyGameStateInstance = nullptr;

    // Uncommented-out sections
    // UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
    // UCurveFloat* CooldownCurve;

private:
    FVector InitialDoorLocation = FVector::ZeroVector;
    FVector TargetDoorLocation = FVector::ZeroVector;

    FTimerHandle CooldownTimerHandle;
    FTimerHandle OpenDoorTimerHandle;
    FTimerHandle ResetDoorTimerHandle;

    UFUNCTION()
    void OpenDoorUpdate(float Value);

    UFUNCTION()
    void ResetDoorUpdate(float Value);

	UFUNCTION()
	void GetAllInstanceClasses();

    // Uncommented-out sections
    // UFUNCTION(Server, Reliable, WithValidation)
    // void CooldownDoorUpdate(float Value);

    // UFUNCTION(Server, Reliable, WithValidation)
    // void StartResetDoorTimer();

    // UFUNCTION(Server, Reliable, WithValidation)
    // void ResetDoor();

    virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;
};