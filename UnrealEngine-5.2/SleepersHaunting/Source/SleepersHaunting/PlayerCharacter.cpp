// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"

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

	if(APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(PlayerMappingContext, 0);
		}
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
		
		// if (MoveInputAction)
		// {
		// 	PlayerEnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered,
		// 		this, &APlayerCharacter::OnMove);
		// }

		// if (JumpInputAction)
		// {
		// 	PlayerEnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Started,
		// 		this, &APlayerCharacter::OnJumpStarted);
		// 	PlayerEnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Completed,
		// 		this, &APlayerCharacter::OnJumpCompleted);
		// }
	}
	
	/*PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	
	PlayerInputComponent->BindAction("Jump",IE_Pressed,this,&ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump",IE_Released,this,&ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Crouch",IE_Pressed,this,&APlayerCharacter::BeginCrouch);
	PlayerInputComponent->BindAction("Crouch",IE_Released,this,&APlayerCharacter::EndCrouch);*/
}

void APlayerCharacter::OnMove(const FInputActionValue& Value)
{
	// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Your Message"));
	// FInputActionValue::Axis2D Axis = Value.Get<FInputActionValue::Axis2D>();

	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (!MovementVector.IsNearlyZero())
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(ForwardDirection, MovementVector.Y);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

// void APlayerCharacter::OnJumpStarted()
// {
// }
//
// void APlayerCharacter::OnJumpCompleted()
// {
// }

// void APlayerCharacter::PawnClientRestart()
// {
// 	Super::PawnClientRestart();
//
// 	
// }

// void APlayerCharacter::MoveForward(float AxisValue)
// {
// 	if ((Controller != nullptr) && (AxisValue != 0.0f))
// 	{
// 		// Find out which way is forward
// 		const FRotator Rotation = Controller->GetControlRotation();
// 		const FRotator YawRotation(0, Rotation.Yaw, 0);
//
// 		// Get forward vector
// 		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
// 		
// 		SetActorRotation(Direction.Rotation());
// 		AddMovementInput(Direction.GetSafeNormal(), 1.0f);
// 	}
// }
//
// void APlayerCharacter::MoveRight(float AxisValue)
// {
// 	if ((Controller != nullptr) && (AxisValue != 0.0f))
// 	{
// 		// Find out which way is right
// 		const FRotator Rotation = Controller->GetControlRotation();
// 		const FRotator YawRotation(0, Rotation.Yaw, 0);
//
// 		// Get right vector
// 		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
//
// 		SetActorRotation(Direction.Rotation());
// 		AddMovementInput(Direction.GetSafeNormal(), 1.0f);
// 	}
// }