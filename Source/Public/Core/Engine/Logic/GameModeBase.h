// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"
#include "UserState.h"

struct FUserId;
class FUSerState;
class FWindowAdvanced;
class FGameModeManager;

/**
 * Base class for game modes.
 */
class FGameModeBase
{
public:
	FGameModeBase(FGameModeManager* InGameModeManager);
	virtual ~FGameModeBase();

	virtual void Initialize();
	virtual void DeInitialize();

	/** Use to start (Calls Start()) */
	void Begin();

	/** Use to end (Calls End()) */
	void Finish();

	/** Creating player instance */
	FPlayerState* AddPlayer();

	/** Creating AI instance */
	FAIState* AddBot();

	/** Remove user or AI by ID */
	bool RemoveUser(const FUserId& InUserIdToRemove);

	virtual bool IsInProgress() const { return bIsInProgress; }

	FGameModeManager* GetGameModeManager() const;
	FWindowAdvanced* GetWindowAdvanced() const;

protected:
	virtual void Start();
	virtual void End();

	/** Override to set custom UserState class for each player */
	virtual FPlayerState* CreatePlayerState(const FUserId& InUserId);

	/** Override to set custom UserState class for each AI */
	virtual FAIState* CreateAIState(const FUserId& InUserId);

private:
	/** Has Start been called? */
	bool bIsInProgress;

	/** Parent */
	FGameModeManager* OwnerGameModeManager;

	/** All user state instances */
	CArray<FUSerState*> UserStateArray;

	/** Current user state index */
	int32 CurrentUserIndex;

};
