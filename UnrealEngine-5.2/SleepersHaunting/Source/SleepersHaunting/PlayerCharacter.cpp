// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	TopDownCameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCameraComp"));
	// Attaching your class Components to the default character's Skeletal Mesh Component.
	//TopDownCameraComp->SetupAttachment(GetMesh());
	TopDownCameraComp->SetRelativeLocationAndRotation(FVector(0.0f, -600.0f, 500.0f), FQuat(FRotator(-30.0f, 90.0f, 0.0f)));
	TopDownCameraComp->bUsePawnControlRotation = false;

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FQuat(FRotator(0.0f, -90.0f, 0.0f)));
	GetMesh()->SetupAttachment(TopDownCameraComp);
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bIgnoreBaseRotation = false;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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
			PlayerEnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered,
				this, &APlayerCharacter::OnMove);
		}

		if (JumpInputAction)
		{
			PlayerEnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Started,
				this, &APlayerCharacter::OnJumpStarted);
			PlayerEnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Completed,
				this, &APlayerCharacter::OnJumpCompleted);
		}
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
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Your Message"));
	FInputActionValue::Axis2D Axis = Value.Get<FInputActionValue::Axis2D>();
}

void APlayerCharacter::OnJumpStarted()
{
}

void APlayerCharacter::OnJumpCompleted()
{
}

void APlayerCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();

	if(APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(PlayerMappingContext, 0);
		}
	}
}

void APlayerCharacter::MoveForward(float AxisValue)
{
	if ((Controller != nullptr) && (AxisValue != 0.0f))
	{
		// Find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		
		SetActorRotation(Direction.Rotation());
		AddMovementInput(Direction.GetSafeNormal(), 1.0f);
	}
}

void APlayerCharacter::MoveRight(float AxisValue)
{
	if ((Controller != nullptr) && (AxisValue != 0.0f))
	{
		// Find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Get right vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		SetActorRotation(Direction.Rotation());
		AddMovementInput(Direction.GetSafeNormal(), 1.0f);
	}
}

void APlayerCharacter::BeginCrouch()
{
	Crouch();
}

void APlayerCharacter::EndCrouch()
{
	UnCrouch();
}
