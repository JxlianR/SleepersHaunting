// Fill out your copyright notice in the Description page of Project Settings.


#include "A_SecuritySwitches.h"

#include "Components/CapsuleComponent.h"

// Sets default values
AA_SecuritySwitches::AA_SecuritySwitches()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*
	SecuritySwitch = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SecuritySMesh"));
	SecuritySwitch->SetupAttachment(RootComponent);

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->SetupAttachment(SecuritySwitch);

	Collider->OnComponentBeginOverlap.AddDynamic(this, &AA_SecuritySwitches::OnOverlapBegin);
	*/

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("SecurityComponent"));
	Collider->SetBoxExtent(FVector(32.f, 32.f, 32.f));
	Collider->SetCollisionProfileName("Trigger");
	RootComponent = Collider;

	Collider->OnComponentBeginOverlap.AddDynamic(this, &AA_SecuritySwitches::OnOverlapBegin);

}

// Called when the game starts or when spawned
void AA_SecuritySwitches::BeginPlay()
{
	Super::BeginPlay();
	GetClosestPlayer();
}

void AA_SecuritySwitches::ActivateSwitch()
{
	if (FindSecurityCamera)
	{
		if (IsLeftSwitch)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("LeftSide!"));

			FindSecurityCamera->PreviousCamera();
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("RightSide!"));

			FindSecurityCamera->NextCamera();
		}
	}
}

void AA_SecuritySwitches::GetClosestPlayer()
{
	float HighestDistance = 0;

	for (APlayerCharacter* Character : Characters)
	{
		float Distance = GetDistanceTo(Character);
		if (Distance > HighestDistance)
		{
			HighestDistance = Distance;
			ClosestCharacter = Character;
		}
	}
}

void AA_SecuritySwitches::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UWorld* World = GetWorld();
	
	if (OtherActor->GetClass()->IsChildOf(APlayerCharacter::StaticClass()) && OtherComponent->IsA(UCapsuleComponent::StaticClass()) && World->IsServer())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("TouchedSwitch!"));
		ActivateSwitch();
	}
}
