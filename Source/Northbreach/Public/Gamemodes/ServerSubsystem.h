// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Online.h"
#include "OnlineSubsystem.h"
#include "ServerSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class NORTHBREACH_API UServerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void CreateDedicatedServerSession(FString InMapPath);

	UFUNCTION()
	void OnSessionCreationReply(FName SessionName, bool bIsSuccessful);

	void FindSessionAndJoin();

	void OnSessionFoundSuccess(bool bWasSuccess);

	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	FOnlineSessionSearch SessionSearch;

	UPROPERTY()
	FString MapPath;

};
