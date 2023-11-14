// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PlayerCharacter.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class SLEEPERSHAUNTING_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PawnClientRestart() override;
	
protected:
	//Player follow camera
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UCameraComponent* TopDownCameraComp;

	//Called for forwards/backward input
	void MoveForward(float InputAxis);

	//called for left/right side input
	void MoveRight(float InputAxis);
	
	//Request for Character to Crouch
	void BeginCrouch();

	//Request for Character to EndCrouch
	void EndCrouch();

	UFUNCTION()
	void OnMove(const FInputActionValue& Value);

	UFUNCTION()
	void OnJumpStarted();

	UFUNCTION()
	void OnJumpCompleted();

protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputMappingContext> PlayerMappingContext;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> MoveInputAction;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> JumpInputAction;

};
