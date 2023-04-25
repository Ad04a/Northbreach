// Fill out your copyright notice in the Description page of Project Settings.


#include "RegisterWidgetBase.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"

void URegisterWidgetBase::NativeOnInitialized()
{
	LoginButton->OnClicked.AddDynamic(this, &URegisterWidgetBase::LoginButtonClicked);
	RegisterButton->OnClicked.AddDynamic(this, &URegisterWidgetBase::RegisterButtonClicked);
	//PasswordField->OnTextCommitted.AddDynamic(this, &URegisterWidgetBase::CheckConfirm);
	//ConfirmPasswordField->OnTextCommitted.AddDynamic(this, &URegisterWidgetBase::CheckConfirm);
}

//void URegisterWidgetBase::CheckConfirm(const FText& Text, ETextCommit::Type CommitMethod)
//{
//	if (PasswordField->GetText().ToString() == ConfirmPasswordField->GetText().ToString())
//	{
//		PasswordErrorMessage->SetText(FText::FromString(""));
//		return;
//	}
//
//	PasswordErrorMessage->SetText(PasswordError);
//}

void URegisterWidgetBase::LoginButtonClicked()
{
	OnLoginButtonClicked.Broadcast();

	
}

void URegisterWidgetBase::RegisterButtonClicked()
{
	if (OnRegisterButtonClicked.IsBound() == false || PasswordErrorMessage->GetText().ToString().Len() > 0)
	{
		return;
	}

	OnRegisterButtonClicked.Execute(Usernamefield->GetText().ToString(), 
													EmailField->GetText().ToString(), 
													PasswordField->GetText().ToString());
}

