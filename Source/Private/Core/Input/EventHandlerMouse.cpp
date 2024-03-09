#include "CoreEngine.h"
#include "Input/EventHandlerMouse.h"
#include "Input/EventHandler.h"

void FMouseInputDelegateWrapper::Execute(const FVector2D<int>& Location, const EInputState InputState)
{
	if (!bWasSentAlready)
	{
		AddToResetQueue();

		if (InputState == EInputState::PRESS && CurrentInputState == EInputState::NOT_PRESSED)
		{
			Delegate.Execute(Location, InputState);

			CurrentInputState = EInputState::PRESS;
		}
		else if (InputState == EInputState::RELEASE && (CurrentInputState == EInputState::PRESS || CurrentInputState == EInputState::NOT_PRESSED))
		{
			Delegate.Execute(Location, InputState);

			bWasSentAlready = true;
		}
	}
}

void FMouseInputDelegateWrapper::AddToResetQueue()
{
	EventHandler->AddMouseInputDelegateToReset(this);
}

void FMouseInputDelegateWrapper::Reset()
{
	bWasSentAlready = false;

	CurrentInputState = EInputState::NOT_PRESSED;
}