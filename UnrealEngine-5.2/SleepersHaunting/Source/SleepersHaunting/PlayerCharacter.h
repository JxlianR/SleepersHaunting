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
#include "Subject.h"
#include "TheTwins.h"
#include "Components/SphereComponent.h"
#include "Components/TextBlock.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

#include "PlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputAction;
class UInputMappingContext;

UCLASS()
class SLEEPERSHAUNTING_API APlayerCharacter : public ACharacter, public Subject
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();
	virtual ~APlayerCharacter() override;
	
	virtual void Jump() override;
	
	virtual void StopJumping() override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* PlayerMappingContext = nullptr;
	
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* MoveInputAction = nullptr;
	
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* JumpInputAction = nullptr;
	
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* GrabInputAction = nullptr;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* RightHandGrabInputAction = nullptr;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* LeftHandGrabInputAction = nullptr;
	
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* TestDebugInputAction = nullptr;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* CloseLeftSlideDoor = nullptr;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* CloseRightSlideDoor = nullptr;
    	
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* UseLeftHandler = nullptr;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* UseRightHandler = nullptr;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* IncreasePowerAction = nullptr;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* StopTwins = nullptr;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* ResumeTwins = nullptr;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* FGroupAttack = nullptr;

	UPROPERTY(EditAnywhere, Replicated)
	float MovementSpeed = 1.0f;

	UPROPERTY(EditAnywhere)
	float JumpVelocity = 0.0f;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPhysicsConstraintComponent* ConstraintComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Collision")
	USphereComponent* RightHandSphereCollision = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Collision")
	USphereComponent* LeftHandSphereCollision = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Handlers")
	UPhysicsHandleComponent* LeftPhysicsHandle = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Handlers")
	UPhysicsHandleComponent* RightPhysicsHandle = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "IK", meta = (AllowPrivateAccess = "true"))
	USceneComponent* LeftHandIKTarget = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "IK", meta = (AllowPrivateAccess = "true"))
	USceneComponent* RightHandIKTarget = nullptr;
	
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

	UPROPERTY()
	ASlideDoors* SlideDoorRightRef = nullptr;

	UPROPERTY()
	ASlideDoors* SlideDoorLeftRef = nullptr;

	UPROPERTY()
	AGarageHandler* GarageHandlerLeftRef = nullptr;

	UPROPERTY()
	AGarageHandler* GarageHandlerRightRef = nullptr;

	UPROPERTY()
	APowerSystem* PowerSystem = nullptr;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UEndOfGameUI> Widget;

	UPROPERTY()
	UEndOfGameUI* WidgetInstance;

	UPROPERTY()
	TArray<ATheTwins*> Twins;

	UFUNCTION(BlueprintCallable, Category = "Audio", NetMulticast, Unreliable)
		void PlayCharacterSound(AActor* Actor);
	
private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* TopDownCameraComponent = nullptr;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom = nullptr;

	//Joao Code---------------------------------------------------------------------------------------
	//Getting the ARoomManager Class
	UPROPERTY()
	ARoomsManager* RoomManagerVariable = nullptr;
	
protected:
	UFUNCTION()
	void OnMove(const FInputActionValue& Value);
	
	void StretchToNearestGrabbable(bool bIsLeftHand);
	void GrabLeft();
	void GrabRight();
	void ReleaseLeft();
	void ReleaseRight();
	UFUNCTION(BlueprintCallable)
	void Grabbing();
	void Release();
	void GrabObject(UPrimitiveComponent* GrabbedComponent, bool bIsLeftHand);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isGrabbing = false;

	UPROPERTY()
	UPrimitiveComponent* GrabbedComponent = nullptr;

	//Joao Code---------------------------------------------------------------------------------------
	UPROPERTY(EditAnywhere, Category = "Audio")
		class USoundCue* CharacterSoundCue = nullptr;
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
	void ForceGroupAttack();

	UFUNCTION()
	void NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

	UFUNCTION(NetMulticast, Reliable)
	void ActivateWidgetEvent(const FText& NewText);
};
