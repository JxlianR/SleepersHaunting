#include "GrabbableObject.h"
#include "Components/StaticMeshComponent.h"

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

	// Log that the object was grabbed
	UE_LOG(LogTemp, Warning, TEXT("Object Grabbed!"));
}
