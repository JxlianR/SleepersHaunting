// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class SLEEPERSHAUNTING_API Observer
{
public:
	Observer();
	virtual ~Observer();

	virtual void Update(const FText& Text) = 0;
};
