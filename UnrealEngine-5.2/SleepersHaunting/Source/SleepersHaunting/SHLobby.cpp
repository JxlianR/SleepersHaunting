// Fill out your copyright notice in the Description page of Project Settings.


#include "SHLobby.h"
#include "Kismet/GameplayStatics.h"

#include "Net/UnrealNetwork.h"

// Sets default values
ASHLobby::ASHLobby()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set default values
	CountPlayer = 0;
	TimerDuration = 10.0f; // Set the duration as needed

	// Create the lobby box component and set it as the root component
	LobbyBox = CreateDefaultSubobject<UBoxComponent>(TEXT("LobbyBox"));
	RootComponent = LobbyBox;

	// Bind functions to handle overlap events
	LobbyBox->OnComponentBeginOverlap.AddDynamic(this, &ASHLobby::OnLobbyEnter);
	LobbyBox->OnComponentEndOverlap.AddDynamic(this, &ASHLobby::OnLobbyExit);
}

// Called when the game starts or when spawned
void ASHLobby::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASHLobby::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASHLobby::OnLobbyEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check if the overlapped actor is a player
	ACharacter* PlayerCharacter = Cast<ACharacter>(OtherActor);
	if (PlayerCharacter)
	{
		// Increment player count
		CountPlayer++;

		// Start the lobby timer if it's the first player
		if (CountPlayer == 2)
		{
			StartLobbyTimer();
		}
	}
}

void ASHLobby::OnLobbyExit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Check if the overlapped actor is a player
	ACharacter* PlayerCharacter = Cast<ACharacter>(OtherActor);
	if (PlayerCharacter)
	{
		// Decrement player count
		CountPlayer--;

		// Stop the lobby timer if there are less than 2 players
		if (CountPlayer < 2)
		{
			StopLobbyTimer();
		}
	}
}

void ASHLobby::StartLobbyTimer()
{
	// Start the timer to open the next level
	GetWorldTimerManager().SetTimer(LobbyTimerHandle, this, &ASHLobby::OpenNextLevel, TimerDuration, false);
}

void ASHLobby::StopLobbyTimer()
{
	// Stop the timer
	if (GetWorldTimerManager().IsTimerActive(LobbyTimerHandle)) {
		GetWorldTimerManager().ClearTimer(LobbyTimerHandle);
	}
}

void ASHLobby::OpenNextLevel()
{
	// Open the next level
	UGameplayStatics::OpenLevel(GetWorld(), FName("PrototypeMap"));
}

void ASHLobby::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASHLobby, CountPlayer);
}