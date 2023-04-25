// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayHUD.h"

#include "UI/Widgets/Gameplay/InteractionWidgetBase.h"

#include "Engine/World.h"

void AGameplayHUD::BeginPlay()
{
	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AGameplayHUD::BeginPlay IsValid(World) == false"));
		return;
	}

	InteractionWidget = CreateWidget<UInteractionWidgetBase>(World, InteractionWidgetClass);
	if (IsValid(InteractionWidget) == false) {
		UE_LOG(LogTemp, Error, TEXT("AMenuHUDBase::BeginPlay() IsValid(LoadingScreenWidget) == false"));
		return;
	}

	PlayerOwner->bShowMouseCursor = false;
	PlayerOwner->SetInputMode(FInputModeGameOnly());
}

void AGameplayHUD::ToggleInteractionWidget(bool bIsShowing, TArray<FInteractionText> InteractionTexts)
{
	if ((IsValid(PlayerOwner) && IsValid(InteractionWidget)) == false) {
		return;
	}
	if (bIsShowing == false)
	{
		InteractionWidget->RemoveFromViewport();
		return;
	}

	FText Basic = FText::FromString("");
	FText Right = FText::FromString("");
	FText Left = FText::FromString("");

	for (FInteractionText Text : InteractionTexts)
	{
		if (Text.Type == EInteractionType::Right)
		{
			Right = Text.Message;
		}
		else if (Text.Type == EInteractionType::Left)
		{
			Left = Text.Message;
		}
		else
		{
			Basic = Text.Message;
		}
	}

	InteractionWidget->SetInteractions(Basic, Right, Left);
	InteractionWidget->AddToViewport();

}

