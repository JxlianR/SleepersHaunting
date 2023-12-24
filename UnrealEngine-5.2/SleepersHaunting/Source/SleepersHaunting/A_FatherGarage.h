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

public:
    

    void SetHandler1(bool NewValue);

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

	

    UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly)
    bool bLosingCondition;

    UPROPERTY(Replicated, BlueprintReadOnly)
    bool bHandler1;

    UPROPERTY(Replicated, BlueprintReadOnly)
    bool bHandler2;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UStaticMeshComponent* GarageDoorMesh;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float ZOffset;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float OpenDoorDuration;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float ResetDoorDuration;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float CooldownDuration;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
    UCurveFloat* OpenDoorCurve;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
    UCurveFloat* ResetDoorCurve;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UTimelineComponent* OpenDoorTimeline;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UTimelineComponent* ResetDoorTimeline;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UTimelineComponent* CooldownDoorTimeline;
	
	class AMyGameState* AMyGameStateInstance;

    // Uncommented-out sections
    // UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
    // UCurveFloat* CooldownCurve;

private:
    FVector InitialDoorLocation;
    FVector TargetDoorLocation;

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