#include "SlideDoors.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASlideDoors::ASlideDoors()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	lockedDoor = false;

	MainMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MainMeshComponent;

	SlideDoorMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SlideDoor"));
	SlideDoorMeshComponent->SetupAttachment(RootComponent);
	SlideDoorMeshComponent->SetSimulatePhysics(true);

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolume"));
	TriggerVolume->SetupAttachment(RootComponent);
	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &ASlideDoors::OnOverlapBegin);
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &ASlideDoors::OnOverlapEnd);
}

// Called when the game starts or when spawned
void ASlideDoors::BeginPlay()
{
	Super::BeginPlay();
	powerSystemReference = Cast<APowerSystem>(UGameplayStatics::GetActorOfClass(GetWorld(), APowerSystem::StaticClass()));
}

// Called every frame
void ASlideDoors::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Force = FVector(-1000.0f, 0.0f, 0.0f); // Adjust the force as needed
	SlideDoorMeshComponent->AddForce(Force);
}

bool ASlideDoors::IsDoorLocked()
{
	return lockedDoor;
}

void ASlideDoors::SetDoorFalse()
{
	lockedDoor = false;
	if (powerSystemReference)
		powerSystemReference->DecreasePowerConsumption();
}

void ASlideDoors::SetDoorTrue()
{
	lockedDoor = true;
	if (powerSystemReference)
		powerSystemReference->IncreasePowerConsumption();
}

void ASlideDoors::SmoothMoveToInitialLocation(float DeltaTime)
{
	// Get initial location
	FVector InitialLocation = SlideDoorMeshComponent->GetComponentLocation();

	// Interpolate towards initial location
	FVector CurrentLocation = SlideDoorMeshComponent->GetComponentLocation();
	FVector NewLocation = FMath::VInterpTo(CurrentLocation, InitialLocation, DeltaTime, 100.0f);

	SlideDoorMeshComponent->SetWorldLocation(NewLocation);
}

void ASlideDoors::Grab_Implementation()
{
	// Start smooth movement when grabbed
	bShouldMoveSmoothly = false;
}

void ASlideDoors::Release_Implementation()
{
	// Stop smooth movement when released
	bShouldMoveSmoothly = true;
}

// Called every frame when grabbed
void ASlideDoors::GrabTick(float DeltaTime)
{
	if (bShouldMoveSmoothly)
	{
		SmoothMoveToInitialLocation(DeltaTime);
	}
}

void ASlideDoors::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check if the overlapping actor is the SlideDoorMeshComponent
	if (OtherComp == SlideDoorMeshComponent)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Triggered"));
		SetDoorTrue();
	}
}

void ASlideDoors::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Check if the overlapping actor is the SlideDoorMeshComponent
	if (OtherComp == SlideDoorMeshComponent)
	{
		// The SlideDoorMeshComponent has stopped overlapping with the TriggerVolume
		SetDoorFalse();
	}
}
