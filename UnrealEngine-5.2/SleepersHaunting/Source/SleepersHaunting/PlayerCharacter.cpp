// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Roomba.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GrabbableInterface.h"
#include "Net/UnrealNetwork.h"
#include "EngineUtils.h"
#include "MyGameState.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/TextBlock.h"
#include "DSP/Chorus.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
    
	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false;
   
	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false;

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));

	/***/
	RightHandSphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("RightHandSphereCollision"));
	RightHandSphereCollision->SetupAttachment(GetMesh(), "hand_r");
	RightHandSphereCollision->InitSphereRadius(7.5f);

	LeftHandSphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("LeftHandSphereCollision"));
	LeftHandSphereCollision->SetupAttachment(GetMesh(), "hand_l");
	LeftHandSphereCollision->InitSphereRadius(7.5f);

	LeftPhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("LeftPhysicsHandle"));
	LeftPhysicsHandle->SetTargetLocation(LeftHandSphereCollision->GetComponentLocation());
	RightPhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("RightPhysicsHandle"));
	RightPhysicsHandle->SetTargetLocation(RightHandSphereCollision->GetComponentLocation());

	LeftHandIKTarget = CreateDefaultSubobject<USceneComponent>(TEXT("LeftHandIKTarget"));
	LeftHandIKTarget->SetupAttachment(GetMesh(), "hand_l");
	
	RightHandIKTarget = CreateDefaultSubobject<USceneComponent>(TEXT("RightHandIKTarget"));
	RightHandIKTarget->SetupAttachment(GetMesh(), "hand_r");
	/***/
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// GetCharacterMovement()->AirControl = 0.2f;
	GetCharacterMovement()->JumpZVelocity = JumpVelocity;
	
	RoomManagerVariable = Cast<ARoomsManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ARoomsManager::StaticClass()));

	SlideDoorLeftRef = FindSlideDoorsByTag(TEXT("SlideDoorL"));
	SlideDoorRightRef = FindSlideDoorsByTag(TEXT("SlideDoorR"));
	
	GarageHandlerLeftRef = FindGarageHandlerByTag(TEXT("GarageHandlerL"));
	GarageHandlerRightRef = FindGarageHandlerByTag(TEXT("GarageHandlerR"));

	PowerSystem = Cast<APowerSystem>(UGameplayStatics::GetActorOfClass(GetWorld(), APowerSystem::StaticClass()));

	UWorld* World = GetWorld();
	for(ATheTwins* Twin : TActorRange<ATheTwins>(World))
	{
		Twins.Add(Twin);
	}

	if(APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(PlayerMappingContext, 0);
		}
	}

	// Bind function to event of Roomba
	ARoomba* Roomba = Cast<ARoomba>(UGameplayStatics::GetActorOfClass(GetWorld(), ARoomba::StaticClass()));
	if (Roomba)
	{
		FScriptDelegate RoombaAttachmentDelegate;
		FScriptDelegate RoombaDetachmentDelegate;
		RoombaAttachmentDelegate.BindUFunction(this, "HandleRoombaAttachedEvent");
		RoombaDetachmentDelegate.BindUFunction(this, "HandleRoombaDetachedEvent");
		Roomba->OnRoombaAttachedEvent.Add(RoombaAttachmentDelegate);
		Roomba->OnRoombaDetachedEvent.Add(RoombaDetachmentDelegate);

		Roomba->GetCharacters();
	}

	// Bind Event to activate UI Widget
	AMyGameState* GameState = Cast<AMyGameState>(UGameplayStatics::GetActorOfClass(GetWorld(), AMyGameState::StaticClass()));
	if (GameState)
	{
		FScriptDelegate ActivateUIDelegate;
		ActivateUIDelegate.BindUFunction(this, "ActivateWidgetEvent");
		GameState->OnActivateUIEvent.Add(ActivateUIDelegate);
	}

	// Create and Add Widget to Viewport
	if (Widget)
	{
		APlayerController* PlayerController = Cast<APlayerController>(GetController());
		WidgetInstance = CreateWidget<UEndOfGameUI>(PlayerController, Widget);

		if (WidgetInstance)
		{
			WidgetInstance->AddToViewport();
			// Hide Widget
			WidgetInstance->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APlayerCharacter, MovementSpeed);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (MoveInputAction)
		{
			PlayerEnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered,this, &APlayerCharacter::OnMove);
		}

		if (JumpInputAction)
		{
			PlayerEnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Started, this, &ACharacter::Jump);
			PlayerEnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		}
		
		/*
		if (GrabInputAction)
		{
			PlayerEnhancedInputComponent->BindAction(GrabInputAction, ETriggerEvent::Triggered, this, &APlayerCharacter::OnGrab);
		}

		if (LeftHandGrabInputAction)
		{
			PlayerEnhancedInputComponent->BindAction(LeftHandGrabInputAction, ETriggerEvent::Triggered, this, &APlayerCharacter::GrabLeft);
			PlayerEnhancedInputComponent->BindAction(LeftHandGrabInputAction, ETriggerEvent::Triggered, this, &APlayerCharacter::ReleaseLeft);
		}
		
		if (RightHandGrabInputAction)
		{
			PlayerEnhancedInputComponent->BindAction(RightHandGrabInputAction, ETriggerEvent::Triggered, this, &APlayerCharacter::GrabRight);
			PlayerEnhancedInputComponent->BindAction(RightHandGrabInputAction, ETriggerEvent::Triggered, this, &APlayerCharacter::ReleaseRight);
		}
		*/
		PlayerInputComponent->BindAction("GrabLeft", IE_Pressed, this, &APlayerCharacter::GrabLeft);
		PlayerInputComponent->BindAction("GrabRight", IE_Pressed, this, &APlayerCharacter::GrabRight);
		PlayerInputComponent->BindAction("GrabLeft", IE_Released, this, &APlayerCharacter::ReleaseLeft);
		PlayerInputComponent->BindAction("GrabRight", IE_Released, this, &APlayerCharacter::ReleaseRight);
		
		if (TestDebugInputAction) 
		{
			//PlayerEnhancedInputComponent->BindAction(TestDebugInputAction, ETriggerEvent::Triggered, this, &APlayerCharacter::CallRoomManagerDebugFunctions);
		}

		if (CloseLeftSlideDoor)
		{
			PlayerEnhancedInputComponent->BindAction(CloseLeftSlideDoor, ETriggerEvent::Started, this, &APlayerCharacter::OnCloseLeftSlideDoor);
			PlayerEnhancedInputComponent->BindAction(CloseLeftSlideDoor, ETriggerEvent::Completed, this, &APlayerCharacter::OnCloseLeftSlideDoorEnd);
		}

		if (CloseRightSlideDoor)
		{
			PlayerEnhancedInputComponent->BindAction(CloseRightSlideDoor, ETriggerEvent::Started, this, &APlayerCharacter::OnCloseRightSlideDoor);
			PlayerEnhancedInputComponent->BindAction(CloseRightSlideDoor, ETriggerEvent::Completed, this, &APlayerCharacter::OnCloseRightSlideDoorEnd);
		}
		
		if (UseLeftHandler)
		{
			PlayerEnhancedInputComponent->BindAction(UseLeftHandler, ETriggerEvent::Started, this, &APlayerCharacter::OnUseLeftHandler);
			PlayerEnhancedInputComponent->BindAction(UseLeftHandler, ETriggerEvent::Completed, this, &APlayerCharacter::OnUseLeftHandlerEnd);
		}

		if (UseRightHandler)
		{
			PlayerEnhancedInputComponent->BindAction(UseRightHandler, ETriggerEvent::Started, this, &APlayerCharacter::OnUseRightHandler);
			PlayerEnhancedInputComponent->BindAction(UseRightHandler, ETriggerEvent::Completed, this, &APlayerCharacter::OnUseRightHandlerEnd);
		}

		if (IncreasePowerAction)
		{
			PlayerEnhancedInputComponent->BindAction(IncreasePowerAction, ETriggerEvent::Started, this, &APlayerCharacter::OnIncreasePower);
		}

		if (StopTwins)
		{
			PlayerEnhancedInputComponent->BindAction(StopTwins, ETriggerEvent::Started, this, &APlayerCharacter::OnStopTwins);
		}

		if (ResumeTwins)
		{
			PlayerEnhancedInputComponent->BindAction(ResumeTwins, ETriggerEvent::Started, this, &APlayerCharacter::OnResumeTwins);
		}
	}
}

ASlideDoors* APlayerCharacter::FindSlideDoorsByTag(const FName& DoorTag)
{
	ASlideDoors* DoorRef = nullptr;
	
	UWorld* World = GetWorld();
	for(ASlideDoors* Door : TActorRange<ASlideDoors>(World))
	{
		if (Door->ActorHasTag(DoorTag))
		{
			DoorRef = Cast<ASlideDoors>(Door);
			break;
		}
	}
	return DoorRef;
}

AGarageHandler* APlayerCharacter::FindGarageHandlerByTag(const FName& HandlerTag)
{
	AGarageHandler* HandlerRef = nullptr;

	UWorld* World = GetWorld();
	for(AGarageHandler* GarageHandler : TActorRange<AGarageHandler>(World))
	{
		if (GarageHandler->ActorHasTag(HandlerTag))
		{
			HandlerRef = Cast<AGarageHandler>(GarageHandler);
			break;
		}
	}

	return HandlerRef;
}

void APlayerCharacter::OnMove(const FInputActionValue& Value)
{
	// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Your Message"));
	// FInputActionValue::Axis2D Axis = Value.Get<FInputActionValue::Axis2D>();
	FVector2D MovementVector = Value.Get<FVector2D>();
	MovementVector.Normalize();

	if (!MovementVector.IsNearlyZero())
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(ForwardDirection, MovementVector.Y * MovementSpeed);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(RightDirection, MovementVector.X * MovementSpeed);
	}
}

void APlayerCharacter::GrabLeft()
{
	StretchToNearestGrabbable(true);
}

void APlayerCharacter::GrabRight()
{
	StretchToNearestGrabbable(false);
}

void APlayerCharacter::ReleaseLeft()
{
	if (LeftPhysicsHandle->GrabbedComponent)
	{
		LeftPhysicsHandle->ReleaseComponent();
	}
}

void APlayerCharacter::ReleaseRight()
{
	if (RightPhysicsHandle->GrabbedComponent)
	{
		RightPhysicsHandle->ReleaseComponent();
	}
}

void APlayerCharacter::StretchToNearestGrabbable(bool bIsLeftHand)
{
	// Get the hand sphere component for the specified hand
	USphereComponent* HandSphere = bIsLeftHand ? LeftHandSphereCollision : RightHandSphereCollision;
	UPhysicsHandleComponent* PhysicsHandle = bIsLeftHand ? LeftPhysicsHandle : RightPhysicsHandle;
	
	// Perform a sphere trace to find grabbable objects in the specified direction
	FVector StartLocation = HandSphere->GetComponentLocation();
	FVector ForwardVector = GetActorForwardVector();
	FVector EndLocation = StartLocation + ForwardVector * MaxGrabDistance;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);  // Ignore the player character

	FHitResult HitResult;
	if (GetWorld()->SweepSingleByChannel(HitResult, StartLocation, EndLocation, FQuat::Identity, ECC_Visibility,
												FCollisionShape::MakeSphere(HandSphere->GetScaledSphereRadius()), CollisionParams))
	{
		// Check if the hit actor implements the grabbable interface
		IGrabbableInterface* GrabbableInterface = Cast<IGrabbableInterface>(HitResult.GetActor());
		if (GrabbableInterface)
		{
			// Stretch the hand towards the grabbable object
			FVector TargetLocation = HitResult.ImpactPoint;
			FVector CurrentLocation = HandSphere->GetComponentLocation();
			FVector NewLocation = FMath::VInterpTo(CurrentLocation, TargetLocation, GetWorld()->GetDeltaSeconds(), StretchSpeed);
			PhysicsHandle->SetTargetLocation(NewLocation);

			// Once the nearest object is found, call GrabObject
			GrabObject(HitResult.GetComponent(), bIsLeftHand);
			GrabbableInterface->Execute_Grab(HitResult.GetActor());
			
			if (bIsLeftHand)
			{
				LeftHandIKTarget->SetWorldLocation(TargetLocation);
			}
			else
			{
				RightHandIKTarget->SetWorldLocation(TargetLocation);
			}
			
			DrawDebugLine(
			GetWorld(),
			StartLocation,
			TargetLocation,
			FColor::Green,  // Change the color if needed
			true,			// Persistent lines
			0,				// Depth priority
			1				// Line thickness
		);
		}
	}
}

void APlayerCharacter::GrabObject(UPrimitiveComponent* GrabbedComponent, bool bIsLeftHand)
{
	if (!GrabbedComponent || !GrabbedComponent->GetOwner())
	{
		return;
	}

	UPhysicsHandleComponent* PhysicsHandle = bIsLeftHand ? LeftPhysicsHandle : RightPhysicsHandle;

	// Attach the grabbed object to the hand
	PhysicsHandle->GrabComponentAtLocation(
		GrabbedComponent,
		NAME_None,
		GrabbedComponent->GetOwner()->GetActorLocation()
	);
}

void APlayerCharacter::OnGrab()
{
	TArray SphereColliders = {RightHandSphereCollision, LeftHandSphereCollision};

    float NearestDistance = TNumericLimits<float>::Max();
    USphereComponent* NearestSphereCollider = nullptr;

	float InteractionRadius = 50.0f;
    for (USphereComponent* Sphere : SphereColliders)
    {
        // Calculate the distance between the player and the sphere collider
        float Distance = FVector::Dist(Sphere->GetComponentLocation(), GetActorLocation());
	
        if (Distance < InteractionRadius && Distance < NearestDistance)
        {
            NearestDistance = Distance;
            NearestSphereCollider = Sphere;
        }
    }

    if (NearestSphereCollider)
    {
        TArray<FOverlapResult> OverlappingActors;
    
        FCollisionShape CollisionShape = FCollisionShape::MakeSphere(InteractionRadius);
        FCollisionQueryParams CollisionParams;
        CollisionParams.AddIgnoredActor(this);
	
        // Get overlapping actors using the nearest sphere collider
        if (GetWorld()->OverlapMultiByChannel(OverlappingActors, NearestSphereCollider->GetComponentLocation(), FQuat::Identity, ECC_GameTraceChannel1, CollisionShape, CollisionParams))
        {
            for (const FOverlapResult& OverlapResult : OverlappingActors)
            {
                if (OverlapResult.GetActor()->GetClass()->ImplementsInterface(UGrabbableInterface::StaticClass()))
                {
                    IGrabbableInterface* GrabbableInterface = Cast<IGrabbableInterface>(OverlapResult.GetActor());
                    if (GrabbableInterface)
                    {
                        GrabbableInterface->Execute_Grab(OverlapResult.GetActor());
                    	
                        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("Grabbable Object Detected: %s"), *NearestSphereCollider->GetName()));
                    }
                }
            }
        }
    }
}

void APlayerCharacter::Jump()
{
	if (CanJump())
	{
		Super::Jump();

		//Detach the Roomba
		TArray<AActor*> Actors;
		GetOverlappingActors(Actors);
	
		for(AActor* Actor : Actors)
		{
			IJumpableInterface* JumpableInterface = Cast<IJumpableInterface>(Actor);
			if (JumpableInterface)
				JumpableInterface->Execute_JumpedOn(Actor, this);
		}
	}

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Jump Called"));
	}
}

void APlayerCharacter::StopJumping()
{
	Super::StopJumping();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, TEXT("StopJumping Called"));
	}
}

void APlayerCharacter::CallRoomManagerDebugFunctions()
{
	/*
	if (RoomManagerVariable)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);

		if (PlayerController)
		{
			// Get the key binding for the DebugAction input action
			bool bIsDebugActionPressed = PlayerController->IsInputKeyDown(EKeys::One);

			// Determine the room ID based on the pressed key
			int32 RoomID = 1;  // Default room ID
			if (bIsDebugActionPressed)
			{
				RoomID = 1;
			}
			// ... repeat for other keys ...

			// Call RoomManager's debug functions with the specified room ID
			RoomManagerVariable->DebugConnectedRooms(RoomID);
			RoomManagerVariable->DebugWaypoints(RoomID);
			RoomManagerVariable->DebugRandomConnectedRoomID(RoomID);
		}
	}
	*/
}

//Julian Code:
void APlayerCharacter::OnCloseLeftSlideDoor()
{
	if (SlideDoorLeftRef)
		SlideDoorLeftRef->SetDoorTrue();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("Close left slide door")));

}

void APlayerCharacter::OnCloseLeftSlideDoorEnd()
{
	if (SlideDoorLeftRef)
		SlideDoorLeftRef->SetDoorFalse();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("Open  left Slide door")));
}

void APlayerCharacter::OnCloseRightSlideDoor()
{
	if (SlideDoorRightRef)
		SlideDoorRightRef->SetDoorTrue();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("Close right slide door")));

}

void APlayerCharacter::OnCloseRightSlideDoorEnd()
{
	if (SlideDoorRightRef)
		SlideDoorRightRef->SetDoorFalse();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("Open right slide door")));

}

void APlayerCharacter::OnUseLeftHandler_Implementation()
{
	if (GarageHandlerLeftRef)
		GarageHandlerLeftRef->SetHandlerTrue();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("Close left handler door")));

}
void APlayerCharacter::OnUseLeftHandlerEnd_Implementation()
{
	if (GarageHandlerLeftRef)
		GarageHandlerLeftRef->SetHandlerFalse();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("Open left handler door")));

}
void APlayerCharacter::OnUseRightHandler_Implementation()
{
	if (GarageHandlerRightRef)
		GarageHandlerRightRef->SetHandlerTrue();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("Close right handler door")));

}
void APlayerCharacter::OnUseRightHandlerEnd_Implementation()
{
	if (GarageHandlerRightRef)
		GarageHandlerRightRef->SetHandlerFalse();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("Open  right handler door")));

}

void APlayerCharacter::OnIncreasePower_Implementation()
{
	if (PowerSystem)
		PowerSystem->AddPower(100.0f);
}

void APlayerCharacter::OnStopTwins()
{
	for(ATheTwins* Twin : Twins)
	{
		Twin->PauseAllTwinTimers();
	}
}

void APlayerCharacter::OnResumeTwins()
{
	for(ATheTwins* Twin : Twins)
	{
		Twin->ResumeAllTwinTimers();
	}
}

//Function that gets triggered through Roomba Event
void APlayerCharacter::HandleRoombaAttachedEvent_Implementation(APlayerCharacter* Character)
{
	if (Character != this) return;
	MovementSpeed = 0.5f;
}

void APlayerCharacter::HandleRoombaDetachedEvent_Implementation()
{
	MovementSpeed = 1.0f;
}

void APlayerCharacter::ActivateWidgetEvent(const FText& NewText)
{
	if(WidgetInstance)
		WidgetInstance->ChangeConditionText(NewText);
}

void APlayerCharacter::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp,
	bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	float CharacterZVelocity = NormalImpulse.Z;
	
	IJumpableInterface* JumpableInterface = Cast<IJumpableInterface>(Other);
	if (JumpableInterface)
		JumpableInterface->Execute_JumpedOn(Other, this);
	
	// if (NormalImpulse.Y > 0.0f)
	// {
	// 	IJumpableInterface* JumpableInterface = Cast<IJumpableInterface>(Other);
	// 	if (JumpableInterface)
	// 		JumpableInterface->Execute_JumpedOn(Other);
	// }
}
