#pragma once

#include "CoreMinimal.h"

/**
 * This class is responsible for managing the tick of the engine
 */
class FTickManager
{
public:
	FTickManager();
	~FTickManager();

	/** This is the main tick function that will be called from the engine (CoreEngine.cpp */
	void EngineTick();

	void BeginTick();
	void Tick();
	void EndTick();


};
