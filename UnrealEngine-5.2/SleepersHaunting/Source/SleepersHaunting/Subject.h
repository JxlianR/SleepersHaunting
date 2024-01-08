// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class Observer;
/**
 * 
 */
class SLEEPERSHAUNTING_API Subject
{
public:
	Subject();
	virtual ~Subject();

	void Attach(Observer* observer);
	void Detach(Observer* observer);

protected:
	void Notify(const FText& Text);

private:
	TArray<Observer*> Observers;
};
