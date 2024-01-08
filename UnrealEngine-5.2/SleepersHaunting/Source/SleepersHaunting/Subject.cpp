// Fill out your copyright notice in the Description page of Project Settings.


#include "Subject.h"
#include "Observer.h"

Subject::Subject()
{
}

Subject::~Subject()
{
	//for (int i = 0; i < observers.Num(); i++)
	//	observers.Remove(observers[i]);
}

void Subject::Attach(Observer* observer)
{
	Observers.Add(observer);
}

void Subject::Detach(Observer* observer)
{
	if (observer == nullptr) return;
	for (int i = 0; i < Observers.Num(); i++)
		if (Observers[i] == observer)
			Observers.Remove(Observers[i]);
}

void Subject::Notify(const FText& Text)
{
	for (int i = 0; i < Observers.Num(); i++)
		Observers[i]->Update(Text);
}
