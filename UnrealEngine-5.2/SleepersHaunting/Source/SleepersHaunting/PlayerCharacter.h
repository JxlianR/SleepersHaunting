// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"

//Classes
#include "RoomsManager.h"
#include "GarageHandler.h"
#include "GrabbableInterface.h"
#include "SlideDoors.h"

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

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* CloseLeftSlideDoor;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* CloseRightSlideDoor;
    	
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* UseLeftHandler;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* UseRightHandler;

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
	void HandleRoombaAttachedEvent(APlayerCharacter* Character);

	UFUNCTION()
	void HandleRoombaDetachedEvent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Class")
		class ASlideDoors* SlideDoorLeftReference;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Class")
		class ASlideDoors* SlideDoorRightReference;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Class")
		class AGarageHandler* GarageHandlerLeftReference;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Class")
		class AGarageHandler* GarageHandlerRightReference;
	
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
	
	// Function to handle grabbing input
	void Grab();
	// Function to handle releasing input
	void Release();
	// Reference to the currently grabbed object
	TScriptInterface<IGrabbableInterface> CurrentlyGrabbedObject;
	private:
	AActor* CurrentlyGrabbedActor;

	//Joao Code---------------------------------------------------------------------------------------
protected:
	UFUNCTION()
	void CallRoomManagerDebugFunctions();
	
	//Julian Code
	UFUNCTION()
	void OnCloseLeftSlideDoor();

	UFUNCTION()
	void OnCloseLeftSlideDoorEnd();
	
	UFUNCTION()
	void OnCloseRightSlideDoor();

	UFUNCTION()
	void OnCloseRightSlideDoorEnd();

	UFUNCTION()
	void OnUseLeftHandler();

	UFUNCTION()
	void OnUseLeftHandlerEnd();

	UFUNCTION()
	void OnUseRightHandler();

	UFUNCTION()
	void OnUseRightHandlerEnd();
	
	UFUNCTION()
	void NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
};
