// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AccountWidgetBase.h"
#include "Headers/UIDelegates.h"

#include "RegisterWidgetBase.generated.h"

DECLARE_DYNAMIC_DELEGATE_ThreeParams(FRegisterButtonClickedSignature, FString, Username,FString, Email, FString, Password);

UCLASS()
class NORTHBREACH_API URegisterWidgetBase : public UAccountWidgetBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* RegisterButton;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* LoginButton;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UEditableTextBox* Usernamefield;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UEditableTextBox* PasswordField;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UEditableTextBox* ConfirmPasswordField;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* PasswordErrorMessage;

	UPROPERTY(EditDefaultsOnly)
	FText PasswordError;

	UFUNCTION()
	void LoginButtonClicked();

	UFUNCTION()
	void RegisterButtonClicked();

	//UFUNCTION()
	//void CheckConfirm(const FText& Text, ETextCommit::Type CommitMethod);

public:
	FButtonClickedSignature OnLoginButtonClicked;
	FRegisterButtonClickedSignature OnRegisterButtonClicked;

	virtual void NativeOnInitialized() override;
};
