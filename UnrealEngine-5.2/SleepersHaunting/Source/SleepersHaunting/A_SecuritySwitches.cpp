// Fill out your copyright notice in the Description page of Project Settings.


#include "A_SecuritySwitches.h"

// Sets default values
AA_SecuritySwitches::AA_SecuritySwitches()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AA_SecuritySwitches::BeginPlay()
{
	Super::BeginPlay();
	
}


void AA_SecuritySwitches::ActivateSwitch()
{
	if (FindSecurityCamera)
	{
		if (IsLeftSwitch)
		{
			FindSecurityCamera->PreviousCamera();
		}
		else
		{
			FindSecurityCamera->NextCamera();
		}
	}
}
