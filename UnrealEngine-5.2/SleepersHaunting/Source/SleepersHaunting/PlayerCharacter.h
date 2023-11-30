// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"

//Classes
#include "RoomsManager.h"

#include "PlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputAction;
class UInputMappingContext;

UCLASS()
class SLEEPERSHAUNTING_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();
	virtual void Jump() override;
	virtual void StopJumping() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* PlayerMappingContext;
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* MoveInputAction;
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* JumpInputAction;
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* GrabInputAction;
	
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* TestDebugInputAction;

	UPROPERTY(EditAnywhere)
	float MovementSpeed = 1.0f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// virtual void PawnClientRestart() override;
	
	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	// Julian Code:
	UFUNCTION()
	void HandleRoombaEvent();
	
private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	//Joao Code---------------------------------------------------------------------------------------
	//Getting the ARoomManager Class
	ARoomsManager* RoomManagerVariable;
	
protected:
	UFUNCTION()
	void OnMove(const FInputActionValue& Value);
	
public:
	UFUNCTION()
	void TryGrab();

	//Joao Code---------------------------------------------------------------------------------------
protected:
	UFUNCTION()
	void CallRoomManagerDebugFunctions();
	
	//Julian Code
	UFUNCTION()
	void NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
};
