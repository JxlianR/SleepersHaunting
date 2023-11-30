// Fill out your copyright notice in the Description page of Project Settings.


#include "Roomba.h"

#include "EngineUtils.h"
#include "Components/SphereComponent.h"
#include "Net/UnrealNetwork.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

// Sets default values
ARoomba::ARoomba()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRooot"));
	RootComponent = DefaultSceneRoot;

	Roomba = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RoombaMesh"));
	Roomba->SetupAttachment(RootComponent);

	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	Collider->SetupAttachment(Roomba);

	Collider->OnComponentBeginOverlap.AddDynamic(this, &ARoomba::OnOverlapBegin);

	SetReplicates(true);
}

// Called when the game starts or when spawned
void ARoomba::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();

	StartLocation = GetActorLocation();
	for(APlayerCharacter* Character : TActorRange<APlayerCharacter>(World))
	{
		Characters.Add(Character);
	}
}

// Called every frame
void ARoomba::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (Attached)
	//	return;
	
	if (Active)
	{
		Lifetime -= DeltaTime;

		if (Lifetime <= 0)
			ChangeActiveState(false);

		if (Attached) return;
		
		GetClosestPlayer();
		FollowPlayer(DeltaTime);

		return;
	}

	if (!Active)
	{
		TimerToActivate -= GetWorld()->DeltaTimeSeconds;
		if (TimerToActivate <= 0)
			ChangeActiveState(true);
	}
}

void ARoomba::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ARoomba, ClosestCharacter);
	DOREPLIFETIME(ARoomba, AttachedCharacter);
	DOREPLIFETIME(ARoomba, StartLocation);
	DOREPLIFETIME(ARoomba, Characters);
}


void ARoomba::GetClosestPlayer_Implementation()
{
	ShortestDistance = 1000000.0f;

	for(int i = 0; i < Characters.Num(); i++)
	{
		if (ClosestCharacter == Characters[i]) continue;
		
		float Distance = GetDistanceTo(Characters[i]);
		if (Distance < ShortestDistance)
		{
			ShortestDistance = Distance;
			ClosestCharacter = Characters[i];
		}
	}
}

void ARoomba::FollowPlayer_Implementation(float DeltaTime)
{
	if (ClosestCharacter == nullptr) return;
	FVector Direction = ClosestCharacter->GetActorLocation() - GetActorLocation();
	Direction.Z = 0.0f;
	SetActorLocation(GetActorLocation() + (Direction * Speed * DeltaTime));
}

void ARoomba::AttachToPlayer_Implementation(APlayerCharacter* Player)
{
	// Needs to be tested in terms of how the roomba is behaving (where does it snap to and what happens when the player is moving)
	const FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, false);
	AttachToActor(Player, AttachmentRules, "Roomba");
	TriggerRoombaAttachedEvent();
	Attached = true;
}

void ARoomba::ChangeActiveState_Implementation(bool active)
{
	Active = active;

	if (!Active)
	{
		const FDetachmentTransformRules DetachmentRules = FDetachmentTransformRules(EDetachmentRule::KeepWorld, true);
		Attached = false;
		DetachFromActor(DetachmentRules);
		AttachedCharacter = nullptr;
		ClosestCharacter = nullptr;
		ShortestDistance = 100000.0f;
		SetActorLocation(StartLocation);
		SetActorRotation(StartRotation);
		Lifetime = InitialLifetime;
	}
	else
	{
		TimerToActivate = InitialTimerToActivate;
	}
}

void ARoomba::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OnOverlapFunction(OverlappedComponent, OtherActor, OtherComponent, OtherBodyIndex, bFromSweep, SweepResult);
}

void ARoomba::OnOverlapFunction_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == ClosestCharacter && AttachedCharacter == nullptr)
	{
		AttachToPlayer(ClosestCharacter);
	}
}

void ARoomba::TriggerRoombaAttachedEvent()
{
	OnRoombaAttachedEvent.Broadcast();
}

void ARoomba::JumpedOn_Implementation()
{
	ChangeActiveState(false);
}



