// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
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
		else if (InputState == EInputState::RELEASE
			&& (CurrentInputState == EInputState::PRESS || CurrentInputState == EInputState::NOT_PRESSED))
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

FEventHandler::FEventHandler(const SDL_Event& InEvent)
	: Event(InEvent)
	, bQuitInputDetected(false)
{
	SetMouseDelegates();
	SetKeyBoardDelegates();
}

FEventHandler::~FEventHandler()
{
	MouseInputDelegateResetQueue.Clear();
	KeyboardInputDelegateResetQueue.Clear();
}

void FEventHandler::HandleEvents()
{
	ResetAll();

	// @TODO SDLK_1 to '1' - Performance Improvement
	
	while (SDL_PollEvent(&Event)) 
	{
		const Uint32 EventType = Event.type;
		
		SwitchOnInput(EventType);
	}
}

void FEventHandler::ResetAll()
{
	for (FMouseInputDelegateWrapper* InputDelegate : MouseInputDelegateResetQueue)
	{
		InputDelegate->Reset();
	}

	MouseInputDelegateResetQueue.Clear();

	for (FInputDelegateWrapper* InputDelegate : KeyboardInputDelegateResetQueue)
	{
		InputDelegate->Reset();
	}

	KeyboardInputDelegateResetQueue.Clear();
}

bool FEventHandler::HasMouseMoved() const
{
	return MouseLocationCurrent != MouseLocationLast;
}

FVector2D<int> FEventHandler::GetMouseLocationCurrent() const
{
	return MouseLocationCurrent;
}

FVector2D<int> FEventHandler::GetMouseLocationLast() const
{
	return MouseLocationLast;
}

void FEventHandler::AddMouseInputDelegateToReset(FMouseInputDelegateWrapper* MouseInputDelegateWrapper)
{
	MouseInputDelegateResetQueue.Push(MouseInputDelegateWrapper);
}

void FEventHandler::AddKeyboardInputDelegateToReset(FInputDelegateWrapper* KeyboardInputDelegateWrapper)
{
	KeyboardInputDelegateResetQueue.Push(KeyboardInputDelegateWrapper);
}

void FEventHandler::SetMouseDelegates()
{
	MouseDelegates.MouseMoveDelegate = FAutoDeletePointer<FMouseInputDelegateWrapper>(this);

	MouseDelegates.MouseLeftButtonDelegate = FAutoDeletePointer<FMouseInputDelegateWrapper>(this);

	MouseDelegates.MouseRightButtonDelegate = FAutoDeletePointer<FMouseInputDelegateWrapper>(this);

	MouseDelegates.MouseMiddleButtonDelegate = FAutoDeletePointer<FMouseInputDelegateWrapper>(this);
}

void FEventHandler::SetKeyBoardDelegates()
{
	KeyBoardDelegates.EscapeDelegate = FAutoDeletePointer<FInputDelegateWrapper>(this);
}

void FEventHandler::SwitchOnInput(const Uint32 EventType)
{
	switch (EventType)
	{
		/** User requested quit */
		case SDL_QUIT:
		{
			bQuitInputDetected = true;

			LOG_DEBUG("Quit input.");

			break;
		}

		/** Window events */
		case SDL_WINDOWEVENT:
		{
			InputWindowEvent();

			break;
		}

		/** Keyboard */
		case SDL_KEYDOWN:
		{
			InputKeyDown();

			break;
		}

		case SDL_KEYUP:
		{
			InputKeyUp();

			break;
		}

		/** Mouse movement X & Y */
		case SDL_MOUSEMOTION:
		{
			MouseMotion();

			break;
		}

		/** Mouse buttons down */
		case SDL_MOUSEBUTTONDOWN:
		{
			InputMouseDown();

			break;
		}

		/** Mouse buttons release */
		case SDL_MOUSEBUTTONUP:
		{
			InputMouseUp();

			break;
		}

		default:
		{
			LOG_DEBUG("Unknown input found. Input: " << Event.type);
		}
	}
}

void FEventHandler::InputKeyUp()
{
	if (Event.key.keysym.sym == SDLK_ESCAPE)
	{
		KeyBoardDelegates.EscapeDelegate->Execute(EInputState::RELEASE);
	}
	else
	{
		LOG_DEBUG("Unknown keyboard input found.");
	}
}

void FEventHandler::MouseMotion()
{
	if (MouseLocationLast != MouseLocationCurrent)
	{
		MouseLocationLast = MouseLocationCurrent;

		MouseDelegates.MouseMoveDelegate->Execute(MouseLocationCurrent, EInputState::PRESS);
	}

	MouseLocationCurrent.X = Event.motion.x;
	MouseLocationCurrent.Y = Event.motion.y;
}

void FEventHandler::InputWindowEvent()
{
	switch (Event.window.event)
	{
		case SDL_WINDOWEVENT_SHOWN:
		{
			LOG_DEBUG("Window " << Event.window.windowID << " shown");
			break;
		}

		case SDL_WINDOWEVENT_HIDDEN:
		{
			LOG_DEBUG("Window " << Event.window.windowID << " hidden");
			GEngine->GetEngineRender()->OnWindowHidden(Event.window.windowID);
			break;
		}

		case SDL_WINDOWEVENT_EXPOSED:
		{
			LOG_DEBUG("Window " << Event.window.windowID << " exposed");
			GEngine->GetEngineRender()->OnWindowExposed(Event.window.windowID);
			break;
		}

		case SDL_WINDOWEVENT_MOVED:
		{
			LOG_DEBUG("Window " << Event.window.windowID << " moved to: " << Event.window.data1 << " " << Event.window.data2);
			GEngine->GetEngineRender()->OnWindowMoved(Event.window.windowID, Event.window.data1, Event.window.data2);
			break;
		}

		case SDL_WINDOWEVENT_RESIZED:
		{
			LOG_DEBUG("Window " << Event.window.windowID << " resized to: " << Event.window.data1 << " " << Event.window.data2);
			GEngine->GetEngineRender()->OnWindowResized(Event.window.windowID, Event.window.data1, Event.window.data2);
			break;
		}

		case SDL_WINDOWEVENT_SIZE_CHANGED:
		{
			LOG_DEBUG("Window " << Event.window.windowID << " size changed to: " << Event.window.data1 << " " << Event.window.data2);
			GEngine->GetEngineRender()->OnWindowSizeChanged(Event.window.windowID, Event.window.data1, Event.window.data2);
			break;
		}

		case SDL_WINDOWEVENT_MINIMIZED:
		{
			LOG_DEBUG("Window " << Event.window.windowID << " minimized.");
			GEngine->GetEngineRender()->OnWindowMinimized(Event.window.windowID);
			break;
		}

		case SDL_WINDOWEVENT_MAXIMIZED:
		{
			LOG_DEBUG("Window " << Event.window.windowID << " maximized.");
			GEngine->GetEngineRender()->OnWindowMaximized(Event.window.windowID);
			break;
		}

		case SDL_WINDOWEVENT_RESTORED:
		{
			LOG_DEBUG("Window " << Event.window.windowID << " restored.");
			break;
		}

		case SDL_WINDOWEVENT_ENTER:
		{
			LOG_DEBUG("Window " << Event.window.windowID << " mouse entered.");
			break;
		}

		case SDL_WINDOWEVENT_LEAVE:
		{
			SDL_Log("Mouse left window %d", Event.window.windowID);
			break;
		}

		case SDL_WINDOWEVENT_FOCUS_GAINED:
		{
			SDL_Log("Window %d gained keyboard focus", Event.window.windowID);
			GEngine->GetEngineRender()->SetWindowFocus(Event.window.windowID, true);
			break;
		}

		case SDL_WINDOWEVENT_FOCUS_LOST:
		{
			LOG_DEBUG("Window " << Event.window.windowID << " lost keyboard focus");
			GEngine->GetEngineRender()->SetWindowFocus(Event.window.windowID, false);
			break;
		}

		case SDL_WINDOWEVENT_CLOSE:
		{
			LOG_DEBUG("Window " << Event.window.windowID << " closed");
			break;
		}

		case SDL_WINDOWEVENT_TAKE_FOCUS:
		{
			LOG_DEBUG("Window " << Event.window.windowID << " is offered a focus");
			break;
		}

		case SDL_WINDOWEVENT_HIT_TEST:
		{
			LOG_DEBUG("Window " << Event.window.windowID << " has a special hit test ");
			break;
		}

		default:
		{
			LOG_DEBUG("Window " << Event.window.windowID << " got unknown event" << Event.window.event);
		}
	}
}

void FEventHandler::InputKeyDown()
{
	switch (Event.key.keysym.sym)
	{
		case SDLK_ESCAPE:
		{
			KeyBoardDelegates.EscapeDelegate->Execute(EInputState::PRESS);

			break;
		}

		case SDLK_1:
		{


			break;
		}
		case SDLK_2:
		{


			break;
		}
		case SDLK_3:
		{


			break;
		}
		case SDLK_4:
		{


			break;
		}
		case SDLK_5:
		{


			break;
		}
		case SDLK_6:
		{


			break;
		}
		case SDLK_7:
		{


			break;
		}
		case SDLK_8:
		{


			break;
		}
		case SDLK_9:
		{


			break;
		}
		case SDLK_0:
		{


			break;
		}

		default:
		{
			LOG_DEBUG("Unknown keyboard input found.");
		}
	}
}

void FEventHandler::InputMouseDown()
{
	switch (Event.button.button)
	{
		case SDL_BUTTON_LEFT:
		{
			MouseDelegates.MouseLeftButtonDelegate->Execute(MouseLocationCurrent, EInputState::PRESS);

			break;
		}

		case SDL_BUTTON_MIDDLE:
		{
			MouseDelegates.MouseMiddleButtonDelegate->Execute(MouseLocationCurrent, EInputState::PRESS);

			break;
		}

		case SDL_BUTTON_RIGHT:
		{
			MouseDelegates.MouseRightButtonDelegate->Execute(MouseLocationCurrent, EInputState::PRESS);

			break;
		}

		default:
		{
			LOG_DEBUG("Unknown mouse input found.");
		}
	}
}

void FEventHandler::InputMouseUp()
{
	switch (Event.button.button)
	{
		case SDL_BUTTON_LEFT:
		{
			MouseDelegates.MouseLeftButtonDelegate->Execute(MouseLocationCurrent, EInputState::RELEASE);

			break;
		}

		case SDL_BUTTON_MIDDLE:
		{
			MouseDelegates.MouseMiddleButtonDelegate->Execute(MouseLocationCurrent, EInputState::RELEASE);

			break;
		}

		case SDL_BUTTON_RIGHT:
		{
			MouseDelegates.MouseRightButtonDelegate->Execute(MouseLocationCurrent, EInputState::RELEASE);

			break;
		}

		default:
		{
			LOG_DEBUG("Unknown mouse input found.");
		}
	}
}

bool FEventHandler::QuitInputDetected() const
{
	return bQuitInputDetected;
}
