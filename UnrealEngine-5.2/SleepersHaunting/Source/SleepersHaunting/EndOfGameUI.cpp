// Fill out your copyright notice in the Description page of Project Settings.


#include "EndOfGameUI.h"

void UEndOfGameUI::ChangeText(FText NewText)
{
	ConditionTextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("Condition")));
	
	if (ConditionTextBlock)
	{
		ConditionTextBlock->SetText(NewText);
		SetVisibility(ESlateVisibility::Visible);
	}
}
