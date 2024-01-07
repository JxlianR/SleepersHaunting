// Fill out your copyright notice in the Description page of Project Settings.


#include "IngameGamemode.h"

void AIngameGamemode::BeginPlay()
{
	Super::BeginPlay();
}

void AIngameGamemode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AIngameGamemode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AIngameGamemode::PreLogin(const FString& Options, const FString& Address,
	const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);

	// Check The Login Tokens
}

APlayerController* AIngameGamemode::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal,
	const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	return Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);
}

void AIngameGamemode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}