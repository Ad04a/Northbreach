// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerSubsystem.h"
//#include "OnlineSybsystemUtils.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

void UServerSubsystem::CreateDedicatedServerSession(FString InMapPath)
{
	IOnlineSessionPtr SessionPtr = Online::GetSessionInterface();
	if (SessionPtr.IsValid() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UServerSubsystem::CreateDedicatedServerSession SessionPtr == false"));
		return;
	}

	MapPath = InMapPath;

	FOnlineSessionSettings SessionCreationSettings;
	SessionCreationSettings.bIsDedicated = true;
	SessionCreationSettings.bShouldAdvertise = true;
	SessionCreationSettings.NumPublicConnections = 10;
	SessionCreationSettings.bAllowJoinInProgress = true;
	SessionCreationSettings.bAllowInvites = false;
	SessionCreationSettings.bUsesPresence = false;
	SessionCreationSettings.bIsLANMatch = false;
	SessionCreationSettings.bAllowJoinViaPresence = false;
	SessionCreationSettings.bAllowJoinViaPresenceFriendsOnly = false;

	SessionCreationSettings.Set(SEARCH_KEYWORDS, SessionIdentifier.ToString(), EOnlineDataAdvertisementType::ViaOnlineService);

	SessionPtr->OnCreateSessionCompleteDelegates.AddUObject(this, &UServerSubsystem::OnSessionCreationReply);
	SessionPtr->CreateSession(0, SessionIdentifier, SessionCreationSettings);
}


void UServerSubsystem::OnSessionCreationReply(FName SessionName, bool bIsSuccessful)
{
	UE_LOG(LogTemp, Display, TEXT("Session %s reply - %d"), *SessionName.ToString(), bIsSuccessful);
	if (bIsSuccessful == false)
	{
		UE_LOG(LogTemp, Error, TEXT("Session creation faild"));
		return;
	}

	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UServerSubsystem::OnSessionCreationReply IsValid(World) == false"));
		return;
	}
	World->ServerTravel(MapPath);
}


void UServerSubsystem::FindSessionAndJoin()
{
	IOnlineSessionPtr SessionPtr = Online::GetSessionInterface();
	if (SessionPtr.IsValid() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UServerSubsystem::FindSessionAndJoin SessionPtr == false"));
		return;
	}
	SessionSearch = MakeShareable(new FOnlineSessionSearch());

	SessionSearch->QuerySettings.Set(SEARCH_KEYWORDS, SessionIdentifier.ToString(), EOnlineComparisonOp::Equals);
	SessionSearch->bIsLanQuery = false;
	UE_LOG(LogTemp, Display, TEXT("Searhing session"));
	SessionPtr->OnFindSessionsCompleteDelegates.AddUObject(this, &UServerSubsystem::OnSessionFoundSuccess);
	SessionPtr->FindSessions(0, SessionSearch.ToSharedRef());
}

void UServerSubsystem::OnSessionFoundSuccess(bool bWasSuccess)
{
	if (bWasSuccess == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UServerSubsystem::OnSessionFoundSuccess Cannot join session"));
		return;
	}
	IOnlineSessionPtr SessionPtr = Online::GetSessionInterface();
	if (SessionPtr.IsValid() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UServerSubsystem::FindSessionAndJoin SessionPtr == false"));
		return;
	}
	if (SessionSearch.IsValid() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UServerSubsystem::FindSessionAndJoin SessionSearch.IsValid() == false"));
		return;
	}
	UE_LOG(LogTemp, Display, TEXT("%d sessions found"), SessionSearch->SearchResults.Num());
	if (SessionSearch->SearchResults.Num() < 1)
	{
		UE_LOG(LogTemp, Error, TEXT("Canceling operation"));
		return;
	}
	
	if (SessionSearch->SearchResults[0].IsValid() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UServerSubsystem::FindSessionAndJoin SessionSearch->SearchResult[0].IsValid() == false"));
		return;
	}
	UE_LOG(LogTemp, Display, TEXT("Trying to join session"));
	SessionPtr->OnJoinSessionCompleteDelegates.AddUObject(this, &UServerSubsystem::OnJoinSessionComplete);
	SessionPtr->JoinSession(0, SessionIdentifier, SessionSearch->SearchResults[0]);
}

void UServerSubsystem::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (Result != EOnJoinSessionCompleteResult::Success)
	{
		UE_LOG(LogTemp, Error, TEXT("UServerSubsystem::OnJoinSessionComplete Cannot join session"));
		return;
	}
	UE_LOG(LogTemp, Display, TEXT("Joining session"));
	FString JoinAdress;
	IOnlineSessionPtr SessionPtr = Online::GetSessionInterface();
	if (SessionPtr.IsValid() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UServerSubsystem::FindSessionAndJoin SessionPtr == false"));
		return;
	}
	SessionPtr->GetResolvedConnectString(FName("Northbreach"), JoinAdress);
	
	if (JoinAdress.IsEmpty() == true)
	{
		UE_LOG(LogTemp, Display, TEXT(" Cannot resolve JoinAdress"));
		return;
	}
	UE_LOG(LogTemp, Display, TEXT("Joining adress: %s"), *JoinAdress);
	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UServerSubsystem::FindSessionAndJoin IsValid(World) == false"));
		return;
	}
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(World, 0);
	PlayerController->ClientTravel(JoinAdress, ETravelType::TRAVEL_Absolute);
}