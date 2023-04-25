// Fill out your copyright notice in the Description page of Project Settings.


#include "ResetPasswordWidgetBase.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"

void UResetPasswordWidgetBase::NativeOnInitialized()
{
	LoginButton->OnClicked.AddDynamic(this, &UResetPasswordWidgetBase::LoginButtonClicked);
	ResetButton->OnClicked.AddDynamic(this, &UResetPasswordWidgetBase::ResetButtonClicked);
}

void UResetPasswordWidgetBase::LoginButtonClicked()
{
	OnLoginButtonClicked.Broadcast();
}

void UResetPasswordWidgetBase::ResetButtonClicked()
{
	if (OnResetButtonClicked.IsBound() == false)
	{
		return;
	}

	OnResetButtonClicked.Execute(EmailField->GetText().ToString());
}