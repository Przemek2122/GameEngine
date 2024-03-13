// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Renderer\WindowAdvanced.h"

#include "Engine/Logic/GameModeManager.h"

FWindowAdvanced::FWindowAdvanced(char* InTitle, int InPositionX, int InPositionY, int InWidth, int InHeight, Uint32 InFlags)
	: FWindow(InTitle, InPositionX, InPositionY, InWidth, InHeight, InFlags)
	, GameModeManager(new FGameModeManager(this))
{
	
}

FWindowAdvanced::~FWindowAdvanced()
{
}
