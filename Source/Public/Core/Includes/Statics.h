// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "Engine.h"
#include "EngineMain.h"

static FEngine* Engine;

template<class FEngineClass = FEngine>
FEngineClass* GetEngine()
{
	return Engine;
}

