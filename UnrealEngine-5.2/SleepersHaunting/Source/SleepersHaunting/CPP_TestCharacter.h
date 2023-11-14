// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "CPP_TestCharacter.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class SLEEPERSHAUNTING_API ACPP_TestCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACPP_TestCharacter();

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
