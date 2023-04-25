// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Headers/UIDelegates.h"

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/EngineTypes.h"

#include "PlayFab.h"
#include "Core/PlayFabError.h"
#include "Core/PlayFabClientDataModels.h"
#include "Core/PlayFabMultiplayerDataModels.h"

#include "NorthbreachGameInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayFabErrorSignature, FString, Message);

UCLASS()
class NORTHBREACH_API UAccountInfo : public UObject
{
	GENERATED_BODY()

public:
	
	PlayFab::ClientModels::FLoginResult LoginInfo;

	FTimerHandle MatchmakingHandle;
	
	FString CurrentQueueName;
	FString CurrentTicketID;
};

UCLASS()
class NORTHBREACH_API UNorthbreachGameInstance : public UGameInstance
{
	GENERATED_BODY()
protected:

	UPROPERTY(EditDefaultsOnly)
	FString TitleID = "D30D1";

	UPROPERTY()
	UAccountInfo* AccountInfo = nullptr;
	
	UPROPERTY(EditDefaultsOnly)
	FName LobbyLevel = "Gameplay";

	UPROPERTY(EditDefaultsOnly)
	FString PathToArena;

	PlayFabClientPtr ClientAPI = nullptr;
	PlayFabMultiplayerPtr MultiplayerAPI = nullptr;

	void OnLoginSuccess(const PlayFab::ClientModels::FLoginResult& Result) const;
	void OnRegisterSuccess(const PlayFab::ClientModels::FRegisterPlayFabUserResult& Result) const;
	void OnResetSuccess(const PlayFab::ClientModels::FSendAccountRecoveryEmailResult& Result) const;
	void OnCreateTicketSuccess(const PlayFab::MultiplayerModels::FCreateMatchmakingTicketResult& Result) const;
	void OnGetTicketSuccess(const PlayFab::MultiplayerModels::FGetMatchmakingTicketResult& Result) const;
	void OnGetMatchSuccess(const PlayFab::MultiplayerModels::FGetMatchResult& Result) const;

	void OnFail(const PlayFab::FPlayFabCppError& ErrorResult) const;

	void GetToLobby() const;
	void CheckIfMatchFound() const;

public:

	FPlayFabErrorSignature OnPlayFabError;
	FButtonClickedSignature OnSuccessfulRegister;
	FButtonClickedSignature OnLevelOpneingStarted;

	virtual void OnStart() override;
	
	UFUNCTION()
	void Register(FString Username, FString Email, FString Password);

	UFUNCTION()
	void Login(FString Email, FString Password);

	UFUNCTION()
	void Reset(FString Email);

	UFUNCTION()
	void CreateMatchmakingTicket(FString QueueName = "Quickplay") const;

	UFUNCTION()
	void GetMatchmakingTicket(FString QueueName = "Quickplay", FString TicketID = "") const;

	UFUNCTION()
	void GetMatch(FString MatchID, FString QueueName = "Quickplay") const;

	bool CanProduceTicket() { return AccountInfo->CurrentTicketID == ""; }
};
