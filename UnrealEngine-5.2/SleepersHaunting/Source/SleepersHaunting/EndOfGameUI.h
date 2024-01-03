// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndOfGameUI.generated.h"

/**
 * 
 */

class UTextBlock;

UCLASS

()
class SLEEPERSHAUNTING_API UEndOfGameUI : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativeConstruct() override;
	
	UFUNCTION(NetMulticast, Reliable)
	void ChangeConditionText(const FText& Text);

protected:
	UPROPERTY()
	UTextBlock* ConditionTextBlock;
};
