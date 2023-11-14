// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_TestCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

// Sets default values
ACPP_TestCharacter::ACPP_TestCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACPP_TestCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_TestCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACPP_TestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (MoveInputAction)
		{
			PlayerEnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered,
				this, &ACPP_TestCharacter::OnMove);
		}

		if (JumpInputAction)
		{
			PlayerEnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Started,
				this, &ACPP_TestCharacter::OnJumpStarted);
			PlayerEnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Completed,
				this, &ACPP_TestCharacter::OnJumpCompleted);
		}
	}

}

void ACPP_TestCharacter::OnMove(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Your Message"));
}

void ACPP_TestCharacter::OnJumpStarted()
{
}

void ACPP_TestCharacter::OnJumpCompleted()
{
}

void ACPP_TestCharacter::PawnClientRestart()
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

