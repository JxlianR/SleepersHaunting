// Fill out your copyright notice in the Description page of Project Settings.

#include "A_FatherGarage.h"

//CLasses include
#include "MyGameState.h"

#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AA_FatherGarage::AA_FatherGarage()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set Defaults Values
	ZOffset = 90.0f;
	bHandler1 = false;
	bHandler2 = false;

	// Initialize timeline Components
	CooldownDoorTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("CooldownDoorTimeline"));
	OpenDoorTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("OpenDoorTimeline"));
	ResetDoorTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("ResetDoorTimeline"));


	if (OpenDoorCurve)
	{
		FOnTimelineFloat OpenDoorUpdateFunction;
		OpenDoorUpdateFunction.BindUFunction(this, FName("OpenDoorUpdate"));
		OpenDoorTimeline->AddInterpFloat(OpenDoorCurve, OpenDoorUpdateFunction);
	}

	if (ResetDoorCurve)
	{
		FOnTimelineFloat ResetDoorUpdateFunction;	
		ResetDoorUpdateFunction.BindUFunction(this, FName("ResetDoorUpdate"));
		ResetDoorTimeline->AddInterpFloat(ResetDoorCurve, ResetDoorUpdateFunction);
	}

	/*
	if (CooldownCurve)
	{
		FOnTimelineFloat CooldownDoorUpdateFunction;
		CooldownDoorUpdateFunction.BindUFunction(this, FName("CooldownDoorUpdate"));
		CooldownDoorTimeline->AddInterpFloat(CooldownCurve, CooldownDoorUpdateFunction);
	}
	*/
}

// Called when the game starts or when spawned
void AA_FatherGarage::BeginPlay()
{
	Super::BeginPlay();

	// Get Initial positions of the garage door
	GetAllInstanceClasses();
	InitialDoorLocation = GetActorLocation();
	TargetDoorLocation = InitialDoorLocation + FVector(0.0f, 0.0f, ZOffset);
	GarageDoorMesh = FindComponentByClass<UStaticMeshComponent>();

	// Bind functions to the timeline events
	if (OpenDoorCurve)
	{
		FOnTimelineFloat OpenDoorUpdateFunction;
		OpenDoorUpdateFunction.BindUFunction(this, FName("OpenDoorUpdate"));
		OpenDoorTimeline->AddInterpFloat(OpenDoorCurve, OpenDoorUpdateFunction);

		FScriptDelegate ScriptDelegate;
		ScriptDelegate.BindUFunction(this, "OnOpenDoorTimelineCompleted");
		OpenDoorTimeline->SetTimelineFinishedFunc(FOnTimelineEvent( ScriptDelegate ));
	}

	if (ResetDoorCurve)
	{
		FOnTimelineFloat ResetDoorUpdateFunction;
		ResetDoorUpdateFunction.BindUFunction(this, FName("ResetDoorUpdate"));
		ResetDoorTimeline->AddInterpFloat(ResetDoorCurve, ResetDoorUpdateFunction);
	}

	/*
	if (CooldownCurve)
	{
		FOnTimelineFloat CooldownDoorUpdateFunction;
		CooldownDoorUpdateFunction.BindUFunction(this, FName("CooldownDoorUpdate"));
		CooldownDoorTimeline->AddInterpFloat(CooldownCurve, CooldownDoorUpdateFunction);
	}
	*/

	// Start the cooldown timer
	StartCooldownTimer();
}


void AA_FatherGarage::StartCooldownTimer()
{
	if(!GetWorld()->IsServer()) return;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Cooldown timer started!"));
	GetWorldTimerManager().SetTimer(CooldownTimerHandle, this, &AA_FatherGarage::StartOpenDoorTimeline, CooldownDuration, false);
}

void AA_FatherGarage::StartOpenDoorTimeline()
{
	if (!bLosingCondition)
	{
		// Start the open door timeline
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Open door timer started!"));
		OpenDoorTimeline->PlayFromStart();
		// Set the timer to close the door after the specified duration
		//GetWorldTimerManager().SetTimer(OpenDoorTimerHandle, this, &AA_FatherGarage::SetLosingConditionTrue, OpenDoorDuration, false);
	}
}

void AA_FatherGarage::OnOpenDoorTimelineCompleted()
{
	SetLosingConditionTrue();
}

void AA_FatherGarage::StartResetTimeline()
{
	// Check if both handlers are true before starting the timeline
	if (bHandler1 && bHandler2)
	{
		StopCooldownTimer();
		StopOpenDoorTimeline();
		
		// Start the ResetDoorTimeline from the beginning
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Reset timer started!"));
		ResetDoorTimeline->PlayFromStart();
		// Set a timer to call CooldownTimerFinished after ResetDoorDuration seconds
		PlayGarageSound();
		GetWorldTimerManager().SetTimer(ResetDoorTimerHandle, this, &AA_FatherGarage::StartCooldownTimer, ResetDoorDuration, false);
	}
}

void AA_FatherGarage::StopCooldownTimer()
{
	if (GetWorldTimerManager().IsTimerActive(CooldownTimerHandle))
	{
		GetWorldTimerManager().ClearTimer(CooldownTimerHandle);
	}
}

void AA_FatherGarage::StopOpenDoorTimeline()
{
	if (OpenDoorTimeline->IsPlaying())
	{
		OpenDoorTimeline->Stop();
	}
}

void AA_FatherGarage::StopResetTimeline()
{
	if (ResetDoorTimeline->IsPlaying())
	{
		ResetDoorTimeline->Stop();
	}
}

void AA_FatherGarage::StopAllTimers()
{
	StopCooldownTimer();
	StopOpenDoorTimeline();
	StopResetTimeline();
}

void AA_FatherGarage::PlayGarageSound()
{
	// Get a reference to the UAudioManager instance.
	UAudioManager& AudioManager = UAudioManager::GetInstance();

	if (GarageSoundCue)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("~Played sound"));
		// Play the sound using the UAudioManager.
		AudioManager.PlaySoundAtLocation(GarageSoundCue, this);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("APlayerCharacter::PlayCharacterSound - Invalid SoundCue"));
	}
}

void AA_FatherGarage::OpenDoorUpdate(float Value)
{
	// Check if the losing condition is false before updating the door's position
	if (!bLosingCondition)
	{
		if (GarageDoorMesh)
		{
			
			// Calculate the new location based on the curve and update the door's position
			FVector NewLocation = FMath::Lerp(InitialDoorLocation, TargetDoorLocation, Value);
			//FVector NewLocation = FMath::Lerp(FVector::ZeroVector, FVector(0.0f, 0.0f, ZOffset), Value);
			//GarageDoorMesh->SetRelativeLocation(NewLocation);
			SetActorLocation(NewLocation);
		}
	}
}

void AA_FatherGarage::ResetDoorUpdate(float Value)
{
	// Check if both handlers are true before updating the door's position
	if (bHandler1 && bHandler2)
	{
		if (GarageDoorMesh)
		{
			// Calculate the new location based on the curve and update the door's position
			FVector NewLocation = FMath::Lerp(TargetDoorLocation, InitialDoorLocation, Value);
			//GarageDoorMesh->SetRelativeLocation(NewLocation);
			SetActorLocation(NewLocation);

		}
	}
}

void AA_FatherGarage::GetAllInstanceClasses()
{
	if (AMyGameState* GameState = Cast<AMyGameState>(UGameplayStatics::GetGameState(GetWorld())))
	{
		AMyGameStateInstance = GameState;
	}
	else if (!AMyGameStateInstance)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Game State Instance not found!"));
	}
}

void AA_FatherGarage::SetHandler1(bool NewValue)
{
	if (GetWorld()->IsServer())
		bHandler1 = NewValue;
}

void AA_FatherGarage::SetHandler2(bool NewValue)
{
	if (GetWorld()->IsServer())
		bHandler2 = NewValue;
}

void AA_FatherGarage::SetLosingConditionTrue()
{
	if (AMyGameStateInstance)
	{
		AMyGameStateInstance->SetLoseCondition(2);
	}
}


//Server Code

void AA_FatherGarage::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//DOREPLIFETIME(AA_FatherGarage, bLosingCondition); //Goes Gamestate class that exists
	DOREPLIFETIME(AA_FatherGarage, bHandler1);
	DOREPLIFETIME(AA_FatherGarage, bHandler2);
}