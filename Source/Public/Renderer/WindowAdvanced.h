// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"

class FGameModeManager;

/**
 * Advanced window
 * + GameModeManager
 */
class FWindowAdvanced : public FWindow
{
public:
	FWindowAdvanced(char* InTitle, int InPositionX, int InPositionY, int InWidth, int InHeight, Uint32 InFlags = WINDOW_DEFAULT_FLAGS);
	~FWindowAdvanced() override;

	/** @TODO Move to subsystem of window */
	FGameModeManager* GetGameModeManager() const { return GameModeManager; }

protected:
	FGameModeManager* GameModeManager;

};