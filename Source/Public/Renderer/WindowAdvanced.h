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
	FWindowAdvanced(char* InTitle, int InPositionX, int InPositionY, int InWidth, int InHeight, Uint32 InFlags = 0);
	~FWindowAdvanced() override;

	FGameModeManager* GetGameModeManager() const { return GameModeManager; }

protected:
	FGameModeManager* GameModeManager;

};