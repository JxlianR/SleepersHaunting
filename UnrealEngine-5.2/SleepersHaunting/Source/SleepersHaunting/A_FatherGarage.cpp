// Fill out your copyright notice in the Description page of Project Settings.


#include "A_FatherGarage.h"
//#include "Components/TimelineComponent.h"
//#include "GameFramework/PlayerController.h"
//#include "Kismet/GameplayStatics.h"

// Sets default values
AA_FatherGarage::AA_FatherGarage()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	
	PrimaryActorTick.bCanEverTick = true;
	
	//Set Defaults Values
	/*
	bCanInteract = true;
	InteractKey = EKeys::F;
	ZOffset = 90.0f;
	*/
	//Initialize timeline Components
	/*
	CooldownDoorTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("CooldownDoorTimeline"));
	OpenDoorTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("OpenDoorTimeline"));
	ResetDoorTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("ResetDoorTimeline"));
	*/

	/*
	if (CooldownCurve)
	{
		FOnTimelineFloat CooldownDoorUpdateFunction;
		CooldownDoorUpdateFunction.BindUFunction(this, FName("CoolDoorUpdate"));
		CooldownDoorTimeline->AddInterpFloat(CooldownCurve, CooldownDoorUpdateFunction);
	}

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
	*/
}

// Called when the game starts or when spawned
void AA_FatherGarage::BeginPlay()
{
	Super::BeginPlay();

	//Get Initial positions of the garage door
	/*
	InitialDoorLocation = GetActorLocation();
	TargetDoorLocation = InitialDoorLocation + FVector(0.0f, 0.0f, ZOffset);


	if (CooldownCurve)
	{
		FOnTimelineFloat CooldownDoorUpdateFunction;
		CooldownDoorUpdateFunction.BindUFunction(this, FName("CoolDoorUpdate"));
		CooldownDoorTimeline->AddInterpFloat(CooldownCurve, CooldownDoorUpdateFunction);
	}

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
	*/
}

// Called every frame
void AA_FatherGarage::Tick(float DeltaTime)
{
	
	Super::Tick(DeltaTime);
	
}

/*
void AA_FatherGarage::OnInteractedPressed()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (bCanInteract && PlayerController && PlayerController->IsInputKeyDown(InteractKey)) {
		bCanInteract = false;
		ResetDoorTimeline->PlayFromStart();
	}
	
}

void AA_FatherGarage::CoolDoorUpdate(float value)
{
	//Making sure the mesh is there
	if (GarageDoorMesh)
    {
        FVector NewLocation = FMath::Lerp(InitialDoorLocation, TargetDoorLocation, Value);
        
        GarageDoorMesh->SetWorldLocation(NewLocation);
    }
}

void AA_FatherGarage::OpenDoorUpdate(float value)
{
	if (GarageDoorMesh)
    {
        FVector NewLocation = FMath::Lerp(InitialDoorLocation, TargetDoorLocation, Value);
        
        GarageDoorMesh->SetWorldLocation(NewLocation);
    }
}

void AA_FatherGarage::ResetDoorUpdate(float value)
{
	if (GarageDoorMesh)
    {
        FVector NewLocation = FMath::Lerp(TargetDoorLocation, InitialDoorLocation, Value);
        
        GarageDoorMesh->SetWorldLocation(NewLocation);
    }
}
*/

