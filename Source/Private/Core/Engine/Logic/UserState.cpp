// Created by Przemys³aw Wiewióra 2024

#include "CoreEngine.h"
#include "Engine/Logic/UserState.h"

FUserId::FUserId(const int32 NewIdNumber)
	: IdNumber(NewIdNumber)
{
}

FUSerState::FUSerState(const FUserId& InUserId)
	: UserId(InUserId)
{
}

FUserId FUSerState::GetUserId() const
{
	return UserId;
}

FPlayerState::FPlayerState(const FUserId& InUserId)
	: FUSerState(InUserId)
{
}

FAIState::FAIState(const FUserId& InUserId)
	: FUSerState(InUserId)
{
}
