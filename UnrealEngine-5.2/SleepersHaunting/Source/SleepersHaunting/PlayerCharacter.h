// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"

//Classes
#include "EndOfGameUI.h"
#include "RoomsManager.h"
#include "GarageHandler.h"
#include "SlideDoors.h"
#include "TheTwins.h"
#include "Components/SphereComponent.h"
#include "Components/TextBlock.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

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
	UInputAction* RightHandGrabInputAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* LeftHandGrabInputAction;
	
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

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* IncreasePowerAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* StopTwins;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* ResumeTwins;

	UPROPERTY(EditAnywhere, Replicated)
	float MovementSpeed = 1.0f;

	UPROPERTY(EditAnywhere)
	float JumpVelocity;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	ASlideDoors* FindSlideDoorsByTag(const FName& DoorTag);

	AGarageHandler* FindGarageHandlerByTag(const FName& HandlerTag);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Collision")
	USphereComponent* RightHandSphereCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Collision")
	USphereComponent* LeftHandSphereCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Handlers")
	UPhysicsHandleComponent* LeftPhysicsHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Handlers")
	UPhysicsHandleComponent* RightPhysicsHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "IK", meta = (AllowPrivateAccess = "true"))
	USceneComponent* LeftHandIKTarget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "IK", meta = (AllowPrivateAccess = "true"))
	USceneComponent* RightHandIKTarget;
	
	// Constants
	UPROPERTY(EditDefaultsOnly, Category = "Grabbable")
	float MaxGrabDistance = 200.0f; // Adjust the value based on your game's requirements

	UPROPERTY(EditDefaultsOnly, Category = "Grabbable")
	float StretchSpeed = 500.0f;
	
	// Julian Code:
	UFUNCTION(Server, Reliable)
	void HandleRoombaAttachedEvent(APlayerCharacter* Character);

	UFUNCTION(Server, Reliable)
	void HandleRoombaDetachedEvent();
	
	ASlideDoors* SlideDoorRightRef;
	
	ASlideDoors* SlideDoorLeftRef;
	
	AGarageHandler* GarageHandlerLeftRef;
	
	AGarageHandler* GarageHandlerRightRef;

	APowerSystem* PowerSystem;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UEndOfGameUI> Widget;

	UPROPERTY()
	UEndOfGameUI* WidgetInstance;

	UPROPERTY()
	TArray<ATheTwins*> Twins;
	
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
	
	void StretchToNearestGrabbable(bool bIsLeftHand);
	void GrabLeft();
	void GrabRight();
	void ReleaseLeft();
	void ReleaseRight();
	void GrabObject(UPrimitiveComponent* GrabbedComponent, bool bIsLeftHand);
	void OnGrab();

	//Joao Code---------------------------------------------------------------------------------------
protected:
	UFUNCTION()
	void CallRoomManagerDebugFunctions();
	
	//Julian Code
	UFUNCTION(Server, Reliable)
	void OnCloseLeftSlideDoor();

	UFUNCTION(Server, Reliable)
	void OnCloseLeftSlideDoorEnd();
	
	UFUNCTION(Server, Reliable)
	void OnCloseRightSlideDoor();

	UFUNCTION(Server, Reliable)
	void OnCloseRightSlideDoorEnd();

	UFUNCTION(Server, Reliable)
	void OnUseLeftHandler();

	UFUNCTION(Server, Reliable)
	void OnUseLeftHandlerEnd();

	UFUNCTION(Server, Reliable)
	void OnUseRightHandler();

	UFUNCTION(Server, Reliable)
	void OnUseRightHandlerEnd();

	UFUNCTION(Server, Reliable)
	void OnIncreasePower();

	UFUNCTION()
	void OnStopTwins();

	UFUNCTION()
	void OnResumeTwins();
	
	UFUNCTION()
	void NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

	UFUNCTION(NetMulticast, Reliable)
	void ActivateWidgetEvent(const FText& NewText);

	// UFUNCTION(NetMulticast, Reliable)
	// void ActivateWidget(FText NewText);
};
