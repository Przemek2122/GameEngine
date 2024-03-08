// Created by Przemys³aw Wiewióra 2020-2024

#include "CoreEngine.h"
#include "Core/Engine/Logic/GameModeBase.h"
#include "Engine/Logic/GameModeManager.h"

FGameModeBase::FGameModeBase(FGameModeManager* InGameModeManager)
	: OwnerGameModeManager(InGameModeManager)
{
}

FGameModeBase::~FGameModeBase()
{
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

void FGameModeBase::Start()
{
}

void FGameModeBase::End()
{
}

FGameModeManager* FGameModeBase::GetOwnerGameModeManager() const
{
	return OwnerGameModeManager;
}
