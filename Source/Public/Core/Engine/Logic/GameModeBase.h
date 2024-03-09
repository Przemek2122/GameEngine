// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"

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
	/** USe to end (Calls End()) */
	void Finish();

	bool IsInProgress() const { return bIsInProgress; }

	FGameModeManager* GetOwnerGameModeManager() const;
	FWindowAdvanced* GetWindowAdvanced() const;

protected:
	virtual void Start();
	virtual void End();

private:
	/** Has Start been called? */
	bool bIsInProgress;

	/** Parent */
	FGameModeManager* OwnerGameModeManager;

};
