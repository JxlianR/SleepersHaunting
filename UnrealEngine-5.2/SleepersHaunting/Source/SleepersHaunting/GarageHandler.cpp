// Fill out your copyright notice in the Description page of Project Settings.


#include "GarageHandler.h"

// Sets default values
AGarageHandler::AGarageHandler()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void AGarageHandler::SetHandlerFalse()
{
	if (GarageReference && bIsHandler1)
	{
		GarageReference->SetHandler1(false);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Handler1 is False"));

	}
	else if (GarageReference && !bIsHandler1)
	{
		GarageReference->SetHandler2(false);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Handler2 is False"));
	}
	else 
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("GarageReference is null"));
	}
}

void AGarageHandler::SetHandlerTrue()
{
	if (GarageReference && bIsHandler1)
	{
		GarageReference->SetHandler1(true);
		GarageReference->StartResetTimeline();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Handler1 is True"));
	}
	else if (GarageReference && !bIsHandler1) 
	{
		GarageReference->SetHandler2(true);
		GarageReference->StartResetTimeline();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Handler2 is True"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("GarageReference is null"));
	}
}
