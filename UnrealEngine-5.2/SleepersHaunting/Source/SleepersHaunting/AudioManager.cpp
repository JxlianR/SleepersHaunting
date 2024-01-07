// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioManager.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

UAudioManager* UAudioManager::Instance = nullptr;

UAudioManager::UAudioManager()
{
	// Initialization code goes here.
}

UAudioManager& UAudioManager::GetInstance()
{
	if (Instance == nullptr)
	{
		Instance = NewObject<UAudioManager>();
		Instance->AddToRoot(); // This ensures that the object won't be garbage collected.
	}

	return *Instance;
}

void UAudioManager::PlaySoundAtLocation(USoundCue* SoundCue, AActor* actor)
{
	if (SoundCue && actor)
	{
		FVector ActorLocation = actor->GetActorLocation();
		UGameplayStatics::PlaySoundAtLocation(actor, SoundCue, ActorLocation);
	}
	else
	{
		// Log a warning using GEngine.
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("UAudioManager::PlaySoundAtLocation - Invalid SoundCue"));
		}
	}
}

void UAudioManager::PlaySound(USoundCue*SoundCue, AActor* actor)
{
	if (SoundCue && actor)
	{
		// Play the sound using UGameplayStatics.
		UGameplayStatics::PlaySound2D(actor, SoundCue);
		//UGameplayStatics::PlaySound2D(GetWorld(), SoundCue, 1.f, 1.f, 0.f, nullptr, bLoop);
		//UGameplayStatics::PlaySound2D(GetWorld(), SoundCue, 1.f, 1.f, 0.f, nullptr, nullptr);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("UAudioManager::PlaySound - Invalid SoundCue"));
	}
}

void UAudioManager::StopSound(USoundCue* SoundCue)
{
	if (SoundCue)
	{
		// Stop the sound by finding and stopping its audio component.
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), FoundActors);

		for (AActor* FoundActor : FoundActors)
		{
			TArray<UAudioComponent*> AudioComponents;
			FoundActor->GetComponents<UAudioComponent>(AudioComponents);

			for (UAudioComponent* AudioComp : AudioComponents)
			{
				if (AudioComp->Sound == SoundCue)
				{
					AudioComp->Stop();
				}
			}
		}
	}
	else
	{
		// Log a warning using GEngine.
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("UAudioManager::StopSound - Invalid SoundCue"));
		}
	}
}

void UAudioManager::StopAllSounds()
{
	// Stop all sounds by finding and stopping all audio components.
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), FoundActors);

	for (AActor* FoundActor : FoundActors)
	{
		TArray<UAudioComponent*> AudioComponents;
		FoundActor->GetComponents<UAudioComponent>(AudioComponents);

		for (UAudioComponent* AudioComp : AudioComponents)
		{
			AudioComp->Stop();
		}
	}
}