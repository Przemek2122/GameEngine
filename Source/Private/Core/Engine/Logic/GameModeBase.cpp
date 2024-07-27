// Created by Przemys³aw Wiewióra 2020-2024

#include "CoreEngine.h"
#include "Core/Engine/Logic/GameModeBase.h"
#include "Engine/Logic/GameModeManager.h"
#include "Engine/Logic/UserState.h"

FGameModeBase::FGameModeBase(FGameModeManager* InGameModeManager)
	: bIsInProgress(false)
	, OwnerGameModeManager(InGameModeManager)
	, CurrentUserIndex(-1)
{
}

FGameModeBase::~FGameModeBase()
{
	for (FUSerState* UserState : UserStateArray)
	{
		delete UserState;
	}

	UserStateArray.Clear();
}

void FGameModeBase::Initialize()
{
}

void FGameModeBase::DeInitialize()
{
}

void FGameModeBase::Begin()
{
	if (!bIsInProgress)
	{
		bIsInProgress = true;

		Start();
	}
}

void FGameModeBase::Finish()
{
	if (bIsInProgress)
	{
		bIsInProgress = false;

		End();
	}
}

FPlayerState* FGameModeBase::AddPlayer()
{
	CurrentUserIndex++;

	FPlayerState* State = CreatePlayerState(FUserId(CurrentUserIndex));

	UserStateArray.Push(State);

	return State;
}

FAIState* FGameModeBase::AddBot()
{
	CurrentUserIndex++;

	FAIState* State = CreateAIState(FUserId(CurrentUserIndex));

	UserStateArray.Push(State);

	return State;
}

bool FGameModeBase::RemoveUser(const FUserId& InUserIdToRemove)
{
	bool bWasRemoved = false;

	for (ContainerInt i = 0; i < UserStateArray.Size(); i++)
	{
		FUSerState* USerState = UserStateArray[i];

		if (USerState->GetUserId() == InUserIdToRemove)
		{
			UserStateArray.RemoveAt(i);

			bWasRemoved = true;

			break;
		}
	}

	return bWasRemoved;
}

void FGameModeBase::Start()
{
}

void FGameModeBase::End()
{
}

FPlayerState* FGameModeBase::CreatePlayerState(const FUserId& InUserId)
{
	return new FPlayerState(InUserId);
}

FAIState* FGameModeBase::CreateAIState(const FUserId& InUserId)
{
	return new FAIState(InUserId);
}

FGameModeManager* FGameModeBase::GetGameModeManager() const
{
	return OwnerGameModeManager;
}

FWindowAdvanced* FGameModeBase::GetWindowAdvanced() const
{
	return OwnerGameModeManager->GetOwnerWindowAdvanced();
}
