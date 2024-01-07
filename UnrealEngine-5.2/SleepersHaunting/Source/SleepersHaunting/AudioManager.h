// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Sound/SoundCue.h"
#include "Engine/Engine.h"
#include "GameFramework/Actor.h"
#include "AudioManager.generated.h"


UCLASS()
class SLEEPERSHAUNTING_API UAudioManager : public UObject
{
	GENERATED_BODY()

private:
	// Private constructor to prevent instantiation from outside.
	UAudioManager();

	// Static pointer to the singleton instance.
	static UAudioManager* Instance;

public:
	// Static method to access the singleton instance.
	static UAudioManager& GetInstance();

	UFUNCTION(BlueprintCallable, Category = "Audio")
		void PlaySoundAtLocation(USoundCue* SoundCue, AActor* actor);

	UFUNCTION(BlueprintCallable, Category = "Audio")
		void PlaySound(USoundCue* SoundCue, AActor* actor);

	UFUNCTION(BlueprintCallable, Category = "Audio")
		void StopSound(USoundCue* SoundCue);

	UFUNCTION(BlueprintCallable, Category = "Audio")
		void StopAllSounds();
};