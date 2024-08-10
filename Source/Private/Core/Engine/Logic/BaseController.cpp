// Created by Przemys³aw Wiewióra 2024

#include "CoreEngine.h"
#include "Engine/Logic/BaseController.h"

FUserId::FUserId(const int32 NewIdNumber)
	: IdNumber(NewIdNumber)
{
}

FBaseController::FBaseController(FEntityManager* InEntityManager, const FUserId& InUserId)
	: EEntity(InEntityManager)
	, UserId(InUserId)
	, PlayerState(nullptr)
{
}

FBaseController::~FBaseController()
{
	delete PlayerState;
}

void FBaseController::BeginPlay()
{
	PlayerState = CreateState();
	PlayerState->BaseController = this;
	PlayerState->BeginPlay();

	EEntity::BeginPlay();
}

void FBaseController::EndPlay()
{
	PlayerState->EndPlay();

	EEntity::EndPlay();
}

FUserId FBaseController::GetUserId() const
{
	return UserId;
}

FState* FBaseController::GetPlayerState() const
{
	return PlayerState;
}

EStateType FBaseController::GetStateType() const
{
	return EStateType::Base;
}

FState* FBaseController::CreateState()
{
	return new FState();
}

FPlayerController::FPlayerController(FEntityManager* InEntityManager, const FUserId& InUserId)
	: FBaseController(InEntityManager, InUserId)
{
}

EStateType FPlayerController::GetStateType() const
{
	return EStateType::Player;
}

FAIController::FAIController(FEntityManager* InEntityManager, const FUserId& InUserId)
	: FBaseController(InEntityManager, InUserId)
{
}

EStateType FAIController::GetStateType() const
{
	return EStateType::AI;
}
