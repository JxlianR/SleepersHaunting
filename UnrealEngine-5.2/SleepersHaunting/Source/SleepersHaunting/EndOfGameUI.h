// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "EndOfGameUI.generated.h"

/**
 * 
 */
UCLASS()
class SLEEPERSHAUNTING_API UEndOfGameUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void ChangeText(FText NewText);

protected:
	UPROPERTY()
	UTextBlock* ConditionTextBlock;
};
