// Created by Przemys³aw Wiewióra 2024

#pragma once

#include "CoreMinimal.h"

class FGameModeBase;

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
 * State of the User
 * This class should exist for each user or AI
 */
class FUSerState
{
public:
	FUSerState(const FUserId& InUserId);

	FUserId GetUserId() const;

private:
	FUserId UserId;

};

/** Player state */
class FPlayerState : public FUSerState
{
public:
	FPlayerState(const FUserId& InUserId);

};

/** AI State */
class FAIState : public FUSerState
{
public:
	FAIState(const FUserId& InUserId);

};
