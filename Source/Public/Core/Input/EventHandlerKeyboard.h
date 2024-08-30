#pragma once

#include "CoreMinimal.h"
#include "Core/Input/EventHandlerShared.h"

/**
 * This class is used to handle keyboard events. It exists to allow rebinding.
 * If delegate returns true it means input is consumed and should not be sent anymore
 */
class FInputDelegateWrapper
{
public:
	FInputDelegateWrapper(FEventHandler* InEventHandler)
		: bWasSentAlready(false)
		, EventHandler(InEventHandler)
		, CurrentInputState(EInputState::NOT_PRESSED)
	{
	}

	void Execute(EInputState InputState);

	void Reset();

	/** Called when input is detected. */
	FDelegate<bool, EInputState> Delegate;

private:
	void AddToResetQueue();

private:
	/** True if input was sent already. */
	bool bWasSentAlready;

	FEventHandler* EventHandler;

	/** Current state of input. It is incremented in execute and then reset in reset */
	EInputState CurrentInputState;
};
