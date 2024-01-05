// Fill out your copyright notice in the Description page of Project Settings.


#include "SHLobby.h"

#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ASHLobby::ASHLobby()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set default values
	CountPlayer = 0;
	TimerDuration = 10.0f; // Set the duration as needed

	// Create the lobby mesh component and set it as the root component
	LobbyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LobbyMesh"));
	RootComponent = LobbyMesh;

	// Set the cube mesh for the LobbyMesh component
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshAsset(TEXT("StaticMesh'/Game/Path/To/Your/CubeMesh.CubeMesh'"));
	if (CubeMeshAsset.Succeeded())
	{
		LobbyMesh->SetStaticMesh(CubeMeshAsset.Object);
	}

	// Bind functions to handle overlap events
	LobbyMesh->OnComponentBeginOverlap.AddDynamic(this, &ASHLobby::OnLobbyEnter);
	LobbyMesh->OnComponentEndOverlap.AddDynamic(this, &ASHLobby::OnLobbyExit);
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
	// Check if the overlapped actor is a player character
	ACharacter* PlayerCharacter = Cast<ACharacter>(OtherActor);
	if (PlayerCharacter)
	{
		// Check if the overlapped component is a capsule component
		UCapsuleComponent* CapsuleComponent = Cast<UCapsuleComponent>(OtherComp);
		if (CapsuleComponent)
		{
			// Increment player count
			CountPlayer++;

			// Display debug message
			FString DebugMessage = FString::Printf(TEXT("Player entered the lobby! Players inside: %d"), CountPlayer);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, DebugMessage);

			// Start the lobby timer if it's the first player
			if (CountPlayer == 2)
			{
				StartLobbyTimer();
			}
		}
	}
}

void ASHLobby::OnLobbyExit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Check if the overlapped actor is a player character
	ACharacter* PlayerCharacter = Cast<ACharacter>(OtherActor);
	if (PlayerCharacter)
	{
		// Check if the overlapped component is a capsule component (commonly used for player bodies)
		UCapsuleComponent* CapsuleComponent = Cast<UCapsuleComponent>(OtherComp);
		if (CapsuleComponent)
		{
			// Decrement player count
			CountPlayer--;

			// Display debug message
			FString DebugMessage = FString::Printf(TEXT("Player exited the lobby! Players inside: %d"), CountPlayer);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, DebugMessage);

			// Stop the lobby timer if there are less than 2 players
			if (CountPlayer < 2)
			{
				StopLobbyTimer();
			}
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
	if (GetWorldTimerManager().IsTimerActive(LobbyTimerHandle))
	{
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