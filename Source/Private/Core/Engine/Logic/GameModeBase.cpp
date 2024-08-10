// Created by Przemys³aw Wiewióra 2020-2024

#include "CoreEngine.h"
#include "Core/Engine/Logic/GameModeBase.h"
#include "Engine/Logic/GameModeManager.h"
#include "Engine/Logic/BaseController.h"

FGameModeBase::FGameModeBase(FGameModeManager* InGameModeManager)
	: bIsInProgress(false)
	, OwnerGameModeManager(InGameModeManager)
	, CurrentUserIndex(-1)
{
	CurrentMap = OwnerGameModeManager->GetOwnerWindowAdvanced()->GetMapManager()->GetCurrentMap();
}

FGameModeBase::~FGameModeBase() = default;

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

FPlayerController* FGameModeBase::AddPlayer()
{
	FPlayerController* NewController = CreatePlayerController();

	UserStateArray.Push(NewController);

	if (NewController != nullptr)
	{
		LOG_INFO("Player created succesfully.");
	}
	else
	{
		LOG_WARN("Player NOT created!");
	}

	return NewController;
}

FAIController* FGameModeBase::AddBot()
{
	FAIController* NewAIController = CreateAIController();

	UserStateArray.Push(NewAIController);

	if (NewAIController != nullptr)
	{
		LOG_INFO("AI created succesfully.");
	}
	else
	{
		LOG_WARN("AI NOT created!");
	}

	return NewAIController;
}

bool FGameModeBase::RemoveUser(const FUserId& InUserIdToRemove)
{
	bool bWasRemoved = false;

	for (ContainerInt i = 0; i < UserStateArray.Size(); i++)
	{
		FBaseController* BaseController = UserStateArray[i];

		if (BaseController->GetUserId() == InUserIdToRemove)
		{
			UserStateArray.RemoveAt(i);

			bWasRemoved = true;

			break;
		}
	}

	return bWasRemoved;
}

FPlayerController* FGameModeBase::GetPlayerControllerByUserId(const FUserId& InUserId)
{
	FPlayerController* Controller = nullptr;

	for (FBaseController* BaseController : UserStateArray)
	{
		if (BaseController->GetUserId() == InUserId)
		{
			Controller = dynamic_cast<FPlayerController*>(BaseController);
		}
	}

	return Controller;
}

FAIController* FGameModeBase::GetAIControllerByUserId(const FUserId& InUserId)
{
	FAIController* Controller = nullptr;

	for (FBaseController* BaseController : UserStateArray)
	{
		if (BaseController->GetUserId() == InUserId)
		{
			Controller = dynamic_cast<FAIController*>(BaseController);
		}
	}

	return Controller;
}

const CArray<FBaseController*>& FGameModeBase::GetControllerArray() const
{
	return UserStateArray;
}

void FGameModeBase::Start()
{
}

void FGameModeBase::End()
{
}

FPlayerController* FGameModeBase::CreatePlayerController()
{
	return CreateController<FPlayerController>();
}

FAIController* FGameModeBase::CreateAIController()
{
	return CreateController<FAIController>();
}

FMap* FGameModeBase::GetCurrentMap() const
{
	return CurrentMap;
}

FGameModeManager* FGameModeBase::GetGameModeManager() const
{
	return OwnerGameModeManager;
}

FWindowAdvanced* FGameModeBase::GetWindowAdvanced() const
{
	return OwnerGameModeManager->GetOwnerWindowAdvanced();
}
