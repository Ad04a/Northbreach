// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginWidgetBase.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"

void ULoginWidgetBase::NativeOnInitialized()
{
	LoginButton->OnClicked.AddDynamic(this, &ULoginWidgetBase::LoginButtonClicked);
	RegisterButton->OnClicked.AddDynamic(this, &ULoginWidgetBase::RegisterButtonClicked);
	ResetButton->OnClicked.AddDynamic(this, &ULoginWidgetBase::ResetButtonClicked);
}

void ULoginWidgetBase::LoginButtonClicked()
{
	if (OnLoginButtonClicked.IsBound() == false)
	{
		return;
	}

	OnLoginButtonClicked.Execute(EmailField->GetText().ToString(), PasswordField->GetText().ToString());
}

void ULoginWidgetBase::RegisterButtonClicked()
{
	OnRegisterButtonClicked.Broadcast();
}

void ULoginWidgetBase::ResetButtonClicked()
{
	OnResetButtonClicked.Broadcast();
}
