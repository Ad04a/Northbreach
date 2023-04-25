// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JoinWidgetBase.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FResetClickedSignature, FString, Email);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FLoginClickedSignature, FString, Email, FString, Password);
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FRegisterClickedSignature, FString, Username, FString, Email, FString, Password);

UCLASS()
class NORTHBREACH_API UJoinWidgetBase : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	class UWidgetSwitcher* ContentSwitcher;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ULoginWidgetBase> LoginWidgetClass;

	class ULoginWidgetBase* LoginWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class URegisterWidgetBase> RegisterWidgetClass;

	class URegisterWidgetBase* RegisterWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UResetPasswordWidgetBase> ResetPasswordWidgetClass;

	class UResetPasswordWidgetBase* ResetPasswordWidget;

	UFUNCTION()
	void ShowRegister();

	UFUNCTION()
	void ShowReset();

	UFUNCTION()
	void LoginClicked(FString Email, FString Password);

	UFUNCTION()
	void RegisterClicked(FString Username, FString Email, FString Password);

	UFUNCTION()
	void ResetClicked(FString Email);

public:
	FResetClickedSignature OnResetClicked;
	FLoginClickedSignature OnLoginClicked;
	FRegisterClickedSignature OnRegisterClicked;

	virtual void NativeOnInitialized() override ;

	UFUNCTION()
	void RecieveErrorMessage(FString Error);

	UFUNCTION()
	void ShowLogin();
};
