// Fill out your copyright notice in the Description page of Project Settings.


#include "AccountWidgetBase.h"

#include "Components/TextBlock.h"

void UAccountWidgetBase::SetErrorMessage(FString Error)
{
	ErrorMessage->SetText(FText::FromString(Error)); 
}