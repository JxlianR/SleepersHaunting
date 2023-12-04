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
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// GetCharacterMovement()->JumpZVelocity = 420.0f;
	// GetCharacterMovement()->AirControl = 0.2f;
	RoomManagerVariable = Cast<ARoomsManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ARoomsManager::StaticClass()));
	SlideDoorRightRef = FindSlideDoorsByName(TEXT("BP_SlideDoorsRight"));
	SlideDoorLeftRef = FindSlideDoorsByName(TEXT("BP_SlideDoorsLeft"));
	GarageHandlerLeftRef = FindGarageHandlerByName(TEXT("BA_GarageHandler"));
	GarageHandlerRightRef = FindGarageHandlerByName(TEXT("BA_GarageHandler2"));


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

ASlideDoors* APlayerCharacter::FindSlideDoorsByName(const FString& DoorName)
{
	ASlideDoors* DoorRef = nullptr;
	TArray<AActor*> SlideDoors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASlideDoors::StaticClass(), SlideDoors);

	for (AActor* Actor : SlideDoors)
	{
		if (Actor->GetName() == DoorName)
		{
			DoorRef = Cast<ASlideDoors>(Actor);
			break;
		}
	}

	return DoorRef;
}

AGarageHandler* APlayerCharacter::FindGarageHandlerByName(const FString& HandlerName)
{
	AGarageHandler* HandlerRef = nullptr;
	TArray<AActor*> GarageHandlers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGarageHandler::StaticClass(), GarageHandlers);

	for (AActor* Actor : GarageHandlers)
	{
		if (Actor->GetName() == HandlerName)
		{
			HandlerRef = Cast<AGarageHandler>(Actor);
			break;
		}
	}

	return HandlerRef;
}
// Called to bind functionality to input
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
			// Ask nelson if this doesnt make sense or if it needs to be started and canceled as TriggerEvents
			PlayerEnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Started, this, &ACharacter::Jump);
			PlayerEnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Canceled, this, &ACharacter::StopJumping);
		}

		if (GrabInputAction)
		{
			PlayerEnhancedInputComponent->BindAction(GrabInputAction, ETriggerEvent::Triggered, this, &APlayerCharacter::OnGrab);
		}
		
		if (TestDebugInputAction) 
		{
			//PlayerEnhancedInputComponent->BindAction(TestDebugInputAction, ETriggerEvent::Triggered, this, &APlayerCharacter::CallRoomManagerDebugFunctions);
		}

		if (CloseLeftSlideDoor)
		{
			PlayerEnhancedInputComponent->BindAction(CloseLeftSlideDoor, ETriggerEvent::Started, this, &APlayerCharacter::OnCloseLeftSlideDoor);
			PlayerEnhancedInputComponent->BindAction(CloseLeftSlideDoor, ETriggerEvent::Canceled, this, &APlayerCharacter::OnCloseLeftSlideDoorEnd);
		}

		if (CloseRightSlideDoor)
		{
			PlayerEnhancedInputComponent->BindAction(CloseRightSlideDoor, ETriggerEvent::Started, this, &APlayerCharacter::OnCloseRightSlideDoor);
			PlayerEnhancedInputComponent->BindAction(CloseRightSlideDoor, ETriggerEvent::Canceled, this, &APlayerCharacter::OnCloseRightSlideDoorEnd);
		}
		
		if (UseLeftHandler)
		{
			PlayerEnhancedInputComponent->BindAction(UseLeftHandler, ETriggerEvent::Started, this, &APlayerCharacter::OnUseLeftHandler);
			PlayerEnhancedInputComponent->BindAction(UseLeftHandler, ETriggerEvent::Canceled, this, &APlayerCharacter::OnUseLeftHandlerEnd);
		}

		if (UseRightHandler)
		{
			PlayerEnhancedInputComponent->BindAction(UseRightHandler, ETriggerEvent::Started, this, &APlayerCharacter::OnUseRightHandler);
			PlayerEnhancedInputComponent->BindAction(UseRightHandler, ETriggerEvent::Canceled, this, &APlayerCharacter::OnUseRightHandlerEnd);
		}
	}
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

void APlayerCharacter::OnGrab()
{
	TArray<FOverlapResult> OverlappingActors;
    
	FCollisionShape CollisionShape = FCollisionShape::MakeSphere(200.0f);
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	// Get overlapping actors
	if (GetWorld()->OverlapMultiByChannel(OverlappingActors, GetActorLocation(), FQuat::Identity, ECC_Visibility, CollisionShape, CollisionParams))
	{
		for (const FOverlapResult& OverlapResult : OverlappingActors)
		{
			if (OverlapResult.GetActor()->GetClass()->ImplementsInterface(UGrabbableInterface::StaticClass()))
			{
				IGrabbableInterface* GrabbableInterface = Cast<IGrabbableInterface>(OverlapResult.GetActor());
				if (GrabbableInterface)
				{
					GrabbableInterface->Execute_Grab(OverlapResult.GetActor());
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Grabbable Object Detected"));
				}
			}
		}
	}
}

void APlayerCharacter::Jump()
{
	if (CanJump())
	{
		FVector JumpImpulse = FVector(0.0f, 0.0f, 100.0f);
		GetCharacterMovement()->AddImpulse(JumpImpulse, true);
		Super::Jump();
	}

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Jump Called"));
	}

	// TArray<AActor*> Actors;
	// GetOverlappingActors(Actors);
	//
	// for(AActor* Actor : Actors)
	// {
	// 	IJumpableInterface* JumpableInterface = Cast<IJumpableInterface>(Actor);
	// 	if (JumpableInterface)
	// 		JumpableInterface->Execute_JumpedOn(Actor);
	// }
}

void APlayerCharacter::StopJumping()
{
	Super::StopJumping();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("StopJumping Called"));
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

void APlayerCharacter::OnUseLeftHandler()
{
	if (GarageHandlerLeftRef)
		GarageHandlerLeftRef->SetHandlerTrue();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("Close left handler door")));

}

void APlayerCharacter::OnUseLeftHandlerEnd()
{
	if (GarageHandlerLeftRef)
		GarageHandlerLeftRef->SetHandlerFalse();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("Open left handler door")));

}
void APlayerCharacter::OnUseRightHandler()
{
	if (GarageHandlerRightRef)
		GarageHandlerRightRef->SetHandlerTrue();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("Close right handler door")));

}

void APlayerCharacter::OnUseRightHandlerEnd()
{
	if (GarageHandlerRightRef)
		GarageHandlerRightRef->SetHandlerFalse();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("Open  right handler door")));

}

//Function that gets triggered through Roomba Event
void APlayerCharacter::HandleRoombaAttachedEvent_Implementation(APlayerCharacter* Character)
{
	//if (Character != this) return;
	MovementSpeed = 0.5f;
}

void APlayerCharacter::HandleRoombaDetachedEvent_Implementation()
{
	MovementSpeed = 1.0f;
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


void APlayerCharacter::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp,
	bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	float CharacterZVelocity = NormalImpulse.Z;

	IJumpableInterface* JumpableInterface = Cast<IJumpableInterface>(Other);
	if (JumpableInterface)
		JumpableInterface->Execute_JumpedOn(Other, this);
	
	/*if (NormalImpulse.Y > 0.0f)
	{
		IJumpableInterface* JumpableInterface = Cast<IJumpableInterface>(Other);
		if (JumpableInterface)
			JumpableInterface->Execute_JumpedOn(Other);
	}*/
}