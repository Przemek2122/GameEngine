#pragma once

#include "CoreMinimal.h"
#include "Core/Input/EventHandlerShared.h"

/** This class is used to handle mouse events. */
class FMouseInputDelegateWrapper
{
public:
	FMouseInputDelegateWrapper(FEventHandler* InEventHandler)
		: bWasSentAlready(false)
		, EventHandler(InEventHandler)
		, CurrentInputState(EInputState::NOT_PRESSED)
	{
	}

	void Execute(const FVector2D<int>& Location, const EInputState InputState);

	void Reset();

	FDelegate<void, FVector2D<int>, EInputState> Delegate;

private:
	void AddToResetQueue();

private:
	/** True if input was sent already. */
	bool bWasSentAlready;

	FEventHandler* EventHandler;

	/** Current state of input. It is incremented in execute and then reset in reset */
	EInputState CurrentInputState;
};
