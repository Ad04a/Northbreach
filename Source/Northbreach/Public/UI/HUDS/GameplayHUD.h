// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Headers/Interactable.h"
#include "GameplayHUD.generated.h"

/**
 * 
 */
UCLASS()
class NORTHBREACH_API AGameplayHUD : public AHUD
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UInteractionWidgetBase> InteractionWidgetClass;

	UPROPERTY()
	class UInteractionWidgetBase* InteractionWidget;

public:

	virtual void BeginPlay() override;

	UFUNCTION()
	void ToggleInteractionWidget(bool bIsShowing, TArray<FInteractionText> InteractionTexts);
};
