// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AccountWidgetBase.h"
#include "Headers/UIDelegates.h"

#include "LoginWidgetBase.generated.h"

DECLARE_DYNAMIC_DELEGATE_TwoParams(FLoginButtonClickedSignature, FString, Email, FString, Password);

UCLASS()
class NORTHBREACH_API ULoginWidgetBase : public UAccountWidgetBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* LoginButton;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* RegisterButton;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* ResetButton;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UEditableTextBox* PasswordField;

	UFUNCTION()
	void LoginButtonClicked();

	UFUNCTION()
	void RegisterButtonClicked();

	UFUNCTION()
	void ResetButtonClicked();

public:
	FLoginButtonClickedSignature OnLoginButtonClicked;
	FButtonClickedSignature OnRegisterButtonClicked;
	FButtonClickedSignature OnResetButtonClicked;

	virtual void NativeOnInitialized() override;
};
