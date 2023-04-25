// Fill out your copyright notice in the Description page of Project Settings.


#include "JoinWidgetBase.h"

#include "LoginWidgetBase.h"
#include "RegisterWidgetBase.h"
#include "ResetPasswordWidgetBase.h"

#include "Components/WidgetSwitcher.h"
#include "Engine/World.h"

void UJoinWidgetBase::NativeOnInitialized()
{
	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UJoinWidgetBase::NativeOnInitialized IsValid(World) == false"));
		return;
	}

	LoginWidget = CreateWidget<ULoginWidgetBase>(World, LoginWidgetClass);
	if (IsValid(LoginWidget) == false) {
		UE_LOG(LogTemp, Error, TEXT("UJoinWidgetBase::NativeOnInitialized IsValid(LoginWidget) == false"));
		return;
	}

	LoginWidget->OnLoginButtonClicked.BindDynamic(this, &UJoinWidgetBase::LoginClicked);
	LoginWidget->OnRegisterButtonClicked.AddDynamic(this, &UJoinWidgetBase::ShowRegister);
	LoginWidget->OnResetButtonClicked.AddDynamic(this, &UJoinWidgetBase::ShowReset);

	RegisterWidget = CreateWidget<URegisterWidgetBase>(World, RegisterWidgetClass);
	if (IsValid(RegisterWidget) == false) {
		UE_LOG(LogTemp, Error, TEXT("UJoinWidgetBase::NativeOnInitialized IsValid(RegisterWidget) == false"));
		return;
	}

	RegisterWidget->OnRegisterButtonClicked.BindDynamic(this, &UJoinWidgetBase::RegisterClicked);
	RegisterWidget->OnLoginButtonClicked.AddDynamic(this, &UJoinWidgetBase::ShowLogin);

	ResetPasswordWidget = CreateWidget<UResetPasswordWidgetBase>(World, ResetPasswordWidgetClass);
	if (IsValid(ResetPasswordWidget) == false) {
		UE_LOG(LogTemp, Error, TEXT("UJoinWidgetBase::NativeOnInitialized IsValid(ResetPasswordWidget) == false"));
		return;
	}

	ResetPasswordWidget->OnResetButtonClicked.BindDynamic(this, &UJoinWidgetBase::ResetClicked);
	ResetPasswordWidget->OnLoginButtonClicked.AddDynamic(this, &UJoinWidgetBase::ShowLogin);

	ContentSwitcher->AddChild(LoginWidget);
	ContentSwitcher->AddChild(RegisterWidget);
	ContentSwitcher->AddChild(ResetPasswordWidget);

}

void UJoinWidgetBase::ShowLogin()
{
	ContentSwitcher->SetActiveWidget(LoginWidget);
}

void UJoinWidgetBase::ShowRegister()
{
	ContentSwitcher->SetActiveWidget(RegisterWidget);
}

void UJoinWidgetBase::ShowReset()
{
	ContentSwitcher->SetActiveWidget(ResetPasswordWidget);
}

void UJoinWidgetBase::LoginClicked(FString Email, FString Password)
{
	if (OnLoginClicked.IsBound() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UJoinWidgetBase::LoginClicked OnLoginClicked.IsBound() == false"));
		return ;
	}
	OnLoginClicked.Execute(Email, Password);
}

void UJoinWidgetBase::RegisterClicked(FString Username, FString Email, FString Password)
{
	if (OnRegisterClicked.IsBound() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UJoinWidgetBase::LoginClicked OnRegisterClicked.IsBound() == false"));
		return;
	}

	OnRegisterClicked.Execute(Username, Email, Password);
}

void UJoinWidgetBase::ResetClicked(FString Email)
{
	if (OnResetClicked.IsBound() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UJoinWidgetBase::LoginClicked OnResetClicked.IsBound() == false"));
		return;
	}

	OnResetClicked.Execute(Email);
}

void UJoinWidgetBase::RecieveErrorMessage(FString Error)
{
	Cast<UAccountWidgetBase>(ContentSwitcher->GetActiveWidget())->SetErrorMessage(Error);
}