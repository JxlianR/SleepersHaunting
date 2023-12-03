// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabbableObject.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AGrabbableObject::AGrabbableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AGrabbableObject::BeginPlay()
{
	Super::BeginPlay();
	
}
void AGrabbableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

USkeletalMeshComponent* PlayerMesh;
	
void AGrabbableObject::GrabObject(ACharacter* PlayerCharacter)
{
    if (PlayerCharacter)
    {
        FName HandSocketName = FName("hand_rSocket");

        // Get the player's mesh component
        PlayerMesh = PlayerCharacter->GetMesh();

        if (PlayerMesh)
        {
            // Attach the object's root component to the player's hand socket
            AttachToComponent(PlayerMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, HandSocketName);

            // Disable physics (if applicable)
            PlayerMesh->SetSimulatePhysics(false);
        }
    }
}

void AGrabbableObject::ReleaseObject()
{
    // Detach the object from the player's hand
    DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

    // Enable physics again
    PlayerMesh->SetSimulatePhysics(true);
	SetActorTickEnabled(true);

    // Optionally, you might want to add some impulse or velocity to the object upon release
    FVector ReleaseImpulse = FVector::ForwardVector * 1000.0f; // Adjust the impulse as needed
    UPrimitiveComponent* RootComp = Cast<UPrimitiveComponent>(RootComponent);
    if (RootComp)
    {
		RootComp->SetSimulatePhysics(true);
        RootComp->AddImpulse(ReleaseImpulse, NAME_None, true);
    }
}
