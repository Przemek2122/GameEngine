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
			bool bInputConsumed = false;

			const FFunctorLambda<bool, FFunctorBase<bool, EInputState>*, EInputState> Lambda(
			[&](FFunctorBase<bool, EInputState>* Function, EInputState) -> bool
			{
				if (!bInputConsumed)
				{
					const bool bFunctionResult = Function->operator()(InputState);
					if (bFunctionResult)
					{
						bInputConsumed = true;
					}
				}

				return bInputConsumed;
			});

			Delegate.ExecuteByLambda(Lambda, InputState);

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
