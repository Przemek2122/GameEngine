#pragma once

#include "CoreMinimal.h"

enum class ERenderPhase : Uint8;

class FRenderInterface;

/**
 * This class is responsible for managing the rendering of the engine
 */
class FEngineRenderingManager
{
public:
	FEngineRenderingManager() = default;
	~FEngineRenderingManager();

	/** Register using delegate with Tick function */
	void RegisterInterface(FFunctorObject<FRenderInterface, void>& TickFunctor, const ERenderPhase TickInterfacePhase);
	void UnRegisterInterface(FFunctorObject<FRenderInterface, void>& TickFunctor, const ERenderPhase TickInterfacePhase);

	/** This is the main tick function that will be called from the engine (CoreEngine.cpp */
	void EngineRender();

	void Render();

	bool HasDelegateIndex(const ERenderPhase Index);

protected:
	void EnsureDelegateAtIndexExists(const ERenderPhase Index);

protected:
	CMap<ERenderPhase, FAutoDeletePointer<FDelegate<void>>> RenderDelegateToIndex;

};
