#include "CoreEngine.h"
#include "Input/EventHandlerKeyboard.h"
#include "Input/EventHandler.h"

void FInputDelegateWrapper::Execute(const EInputState InputState)
{
	if (!bWasSentAlready)
	{
		AddToResetQueue();

		if (EInputState::PRESS == InputState && CurrentInputState == EInputState::NOT_PRESSED)
		{
			Delegate.Execute(InputState);

			CurrentInputState = EInputState::PRESS;
		}
		else if (EInputState::RELEASE == InputState
			&& (CurrentInputState == EInputState::PRESS || CurrentInputState == EInputState::NOT_PRESSED))
		{
			Delegate.Execute(InputState);

			bWasSentAlready = true;
		}
	}
}

void FInputDelegateWrapper::Reset()
{
	bWasSentAlready = false;

	CurrentInputState = EInputState::NOT_PRESSED;
}

void FInputDelegateWrapper::AddToResetQueue()
{
	EventHandler->AddKeyboardInputDelegateToReset(this);
}
