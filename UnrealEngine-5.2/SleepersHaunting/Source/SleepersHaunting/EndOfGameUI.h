// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Observer.h"
#include "Blueprint/UserWidget.h"
#include "EndOfGameUI.generated.h"

/**
 * 
 */

class UTextBlock;

UCLASS

()
class SLEEPERSHAUNTING_API UEndOfGameUI : public UUserWidget, public Observer
{
	GENERATED_BODY()

public:
	void NativeConstruct() override;
	
	UFUNCTION()
	void ChangeConditionText(const FText& Text);

	void Update(const FText& Text) override;

protected:
	UPROPERTY()
	UTextBlock* ConditionTextBlock;
};
