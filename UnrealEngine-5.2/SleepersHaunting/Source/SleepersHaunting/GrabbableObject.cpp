#include "GrabbableObject.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"

AGrabbableObject::AGrabbableObject()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create the mesh component
	GrabbableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = GrabbableMesh;
}

void AGrabbableObject::BeginPlay()
{
	Super::BeginPlay();
}

void AGrabbableObject::Grab_Implementation()
{
	// Implement grabbing logic here
	FTransform NewTransform = this->GetActorTransform();

	LerpAlpha = FMath::Clamp(LerpAlpha + (10 * LerpSpeed), 0.0f, 1.0f);
	NewTransform.SetLocation(TargetLocation);
	FVector NewLocation = FMath::Lerp(InitialLocation, TargetLocation, LerpAlpha);
	SetActorLocation(NewLocation);
	
	// Log that the object was grabbed
	UE_LOG(LogTemp, Warning, TEXT("Object Grabbed!"));
}

void AGrabbableObject::Release_Implementation()
{
	
}
