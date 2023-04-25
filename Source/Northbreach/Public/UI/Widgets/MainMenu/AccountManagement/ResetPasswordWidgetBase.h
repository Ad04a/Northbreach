// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AccountWidgetBase.h"
#include "UIDelegates.h"

#include "ResetPasswordWidgetBase.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FResetButtonClickedSignature, FString, Email);

UCLASS()
class NORTHBREACH_API UResetPasswordWidgetBase : public UAccountWidgetBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* ResetButton;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* LoginButton;

	UFUNCTION()
	void LoginButtonClicked();

	UFUNCTION()
	void ResetButtonClicked();

public:
	FButtonClickedSignature OnLoginButtonClicked;
	FResetButtonClickedSignature OnResetButtonClicked;

	virtual void NativeOnInitialized() override;
};
