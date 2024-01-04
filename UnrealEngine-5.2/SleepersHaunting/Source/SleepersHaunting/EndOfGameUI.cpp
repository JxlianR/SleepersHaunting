// Fill out your copyright notice in the Description page of Project Settings.


#include "EndOfGameUI.h"

#include "Components/TextBlock.h"

void UEndOfGameUI::NativeConstruct()
{
	Super::NativeConstruct();

	ConditionTextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("Condition")));
}

void UEndOfGameUI::ChangeConditionText(const FText& Text)
{
	if(ConditionTextBlock)
	{
		ConditionTextBlock->SetText(Text);
		SetVisibility(ESlateVisibility::Visible);
	}
}

void UEndOfGameUI::Update(const FText& Text)
{
	if(ConditionTextBlock)
	{
		ConditionTextBlock->SetText(Text);
		SetVisibility(ESlateVisibility::Visible);
	}
}
