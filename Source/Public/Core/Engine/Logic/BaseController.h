// Created by Przemys³aw Wiewióra 2024

#pragma once

#include "CoreMinimal.h"

class FBaseController;
class FGameModeBase;

enum EStateType
{
	Base,
	Player,
	AI
};

/**
 * User Id for disallowing to provide raw Id.
 * It should always come from object.
 */
struct FUserId
{
	friend FGameModeBase;

private:
	FUserId(const int32 NewIdNumber);

public:
	/** Get raw integer */
	int32 Get() const { return IdNumber; }

	/** Utility to compare FUserId */
	bool operator==(const FUserId& Other) const { return IdNumber == Other.IdNumber; }

private:
	int32 IdNumber;
	
};

/**
 * Class for data shared between AI and player like
 * resources for current game etc...
 */
class FState
{
	friend FBaseController;

public:
	virtual ~FState() = default;

	virtual void BeginPlay()
	{
	}

	virtual void EndPlay()
	{
	}

	FBaseController* GetController() const { return BaseController; }

protected:
	FBaseController* BaseController;
	
};

/** This class should exist for each user or AI */
class FBaseController : public EEntity
{
public:
	FBaseController(FEntityManager* InEntityManager, const FUserId& InUserId);
	~FBaseController() override;

	void BeginPlay() override;
	void EndPlay() override;

	FUserId GetUserId() const;

	FState* GetPlayerState() const;

	virtual EStateType GetStateType() const;

protected:
	virtual FState* CreateState();

private:
	/** Unique id for each player */
	FUserId UserId;

	/** Player state class for each user */
	FState* PlayerState;

};

/** Player */
class FPlayerController : public FBaseController
{
public:
	FPlayerController(FEntityManager* InEntityManager, const FUserId& InUserId);

	EStateType GetStateType() const override;

};

/** AI */
class FAIController : public FBaseController
{
public:
	FAIController(FEntityManager* InEntityManager, const FUserId& InUserId);

	EStateType GetStateType() const override;

};
