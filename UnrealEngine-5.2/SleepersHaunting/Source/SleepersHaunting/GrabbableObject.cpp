// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabbableObject.h"

// Sets default values
AGrabbableObject::AGrabbableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGrabbableObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGrabbableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGrabbableObject::Grab_Implementation(AActor* Actor)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("grab"));
	// FVector Loc = FVector(10,0,7);
	// SetActorLocation(Loc);
}

