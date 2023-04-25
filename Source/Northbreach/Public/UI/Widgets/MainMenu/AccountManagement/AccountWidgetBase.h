// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AccountWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class NORTHBREACH_API UAccountWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UEditableTextBox* EmailField;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* ErrorMessage;

public:

	void SetErrorMessage(FString Error);
};
