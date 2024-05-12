// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Input/EventHandler.h"

#include "Assets/IniReader/IniManager.h"
#include "Assets/IniReader/IniObject.h"

FMouseDelegates::FMouseDelegates(FEventHandler* EventHandler)
{
	AddInput(EventHandler, "Default");

	AddInput(EventHandler, "Move");
	AddInput(EventHandler, "LeftButton");
	AddInput(EventHandler, "MiddleButton");
	AddInput(EventHandler, "RightButton");
}

void FMouseDelegates::AddInput(FEventHandler* EventHandler, const std::string& InputName)
{
#if _DEBUG
	if (EventHandler != nullptr)
	{
#endif

		InputNameToDelegateMap.Emplace(InputName, FAutoDeletePointer<FMouseInputDelegateWrapper>(EventHandler));

#if _DEBUG
	}
	else
	{
		LOG_ERROR("EventHandler can not be nullptr!");
	}
#endif
}

FMouseInputDelegateWrapper* FMouseDelegates::GetMouseDelegateByName(const std::string& InputName)
{
	if (InputNameToDelegateMap.ContainsKey(InputName))
	{
		return InputNameToDelegateMap[InputName].Get();
	}
	else
	{
		LOG_ERROR("FMouseDelegates::GetMouseDelegateByName returns default input mapping. It will not work.");

		return InputNameToDelegateMap["Default"].Get();
	}
}

FKeyBoardDelegates::FKeyBoardDelegates(FEventHandler* EventHandler)
{
	AddInput(EventHandler, "Default");


}

void FKeyBoardDelegates::AddInput(FEventHandler* EventHandler, const std::string& InputName)
{
#if _DEBUG
	if (EventHandler != nullptr)
	{
#endif

		InputNameToDelegateMap.Emplace(InputName, FAutoDeletePointer<FInputDelegateWrapper>(EventHandler));

#if _DEBUG
	}
	else
	{
		LOG_ERROR("EventHandler can not be nullptr!");
	}
#endif
}

FInputDelegateWrapper* FKeyBoardDelegates::GetMouseDelegateByName(const std::string& InputName)
{
	if (InputNameToDelegateMap.ContainsKey(InputName))
	{
		return InputNameToDelegateMap[InputName].Get();
	}
	else
	{
		LOG_ERROR("FKeyBoardDelegates::GetMouseDelegateByName returns default input mapping. It will not work.");

		return InputNameToDelegateMap["Default"].Get();
	}
}

FEventHandler::FEventHandler(const SDL_Event& InEvent)
	: MouseDelegates(this)
	, KeyBoardDelegates(this)
	, Event(InEvent)
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

void FEventHandler::InitializeInputFromConfig()
{
	FIniManager* IniManager = GEngine->GetAssetsManager()->GetIniManager();
	EngineInputIniObject = IniManager->GetIniObject("EngineInput");
	if (EngineInputIniObject->DoesIniExist())
	{
		EngineInputIniObject->LoadIni();

		FIniField IniField = EngineInputIniObject->FindFieldByName("InputA");

		LOG_INFO("IniField key: " << IniField.GetName() << ", value: " << IniField.GetValueAsString());
	}
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

bool FEventHandler::QuitInputDetected() const
{
	return bQuitInputDetected;
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
}

void FEventHandler::SetKeyBoardDelegates()
{
	KeyBoardDelegates.ButtonEscape = FAutoDeletePointer<FInputDelegateWrapper>(this);

	KeyBoardDelegates.Button0 = FAutoDeletePointer<FInputDelegateWrapper>(this);
	KeyBoardDelegates.Button1 = FAutoDeletePointer<FInputDelegateWrapper>(this);
	KeyBoardDelegates.Button2 = FAutoDeletePointer<FInputDelegateWrapper>(this);
	KeyBoardDelegates.Button3 = FAutoDeletePointer<FInputDelegateWrapper>(this);
	KeyBoardDelegates.Button4 = FAutoDeletePointer<FInputDelegateWrapper>(this);
	KeyBoardDelegates.Button5 = FAutoDeletePointer<FInputDelegateWrapper>(this);
	KeyBoardDelegates.Button6 = FAutoDeletePointer<FInputDelegateWrapper>(this);
	KeyBoardDelegates.Button7 = FAutoDeletePointer<FInputDelegateWrapper>(this);
	KeyBoardDelegates.Button8 = FAutoDeletePointer<FInputDelegateWrapper>(this);
	KeyBoardDelegates.Button9 = FAutoDeletePointer<FInputDelegateWrapper>(this);

	KeyBoardDelegates.ButtonA = FAutoDeletePointer<FInputDelegateWrapper>(this);
	KeyBoardDelegates.ButtonB = FAutoDeletePointer<FInputDelegateWrapper>(this);
	KeyBoardDelegates.ButtonC = FAutoDeletePointer<FInputDelegateWrapper>(this);
	KeyBoardDelegates.ButtonD = FAutoDeletePointer<FInputDelegateWrapper>(this);
	KeyBoardDelegates.ButtonE = FAutoDeletePointer<FInputDelegateWrapper>(this);
	// [...] @TODO Add other basic buttons
	KeyBoardDelegates.ButtonW = FAutoDeletePointer<FInputDelegateWrapper>(this);
	KeyBoardDelegates.ButtonS = FAutoDeletePointer<FInputDelegateWrapper>(this);

	KeyBoardDelegates.ButtonArrowUP = FAutoDeletePointer<FInputDelegateWrapper>(this);
	KeyBoardDelegates.ButtonArrowDOWN = FAutoDeletePointer<FInputDelegateWrapper>(this);
	KeyBoardDelegates.ButtonArrowRIGHT = FAutoDeletePointer<FInputDelegateWrapper>(this);
	KeyBoardDelegates.ButtonArrowLEFT = FAutoDeletePointer<FInputDelegateWrapper>(this);

	KeyBoardDelegates.ButtonDELETE = FAutoDeletePointer<FInputDelegateWrapper>(this);
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

void FEventHandler::InputKeyDown()
{
	switch (Event.key.keysym.sym)
	{
		case SDLK_ESCAPE:
		{
			KeyBoardDelegates.ButtonEscape->Execute(EInputState::PRESS);

			break;
		}

		case SDLK_0:
		{
			KeyBoardDelegates.Button0->Execute(EInputState::PRESS);

			break;
		}
		case SDLK_1:
		{
			KeyBoardDelegates.Button1->Execute(EInputState::PRESS);

			break;
		}
		case SDLK_2:
		{
			KeyBoardDelegates.Button2->Execute(EInputState::PRESS);

			break;
		}
		case SDLK_3:
		{
			KeyBoardDelegates.Button3->Execute(EInputState::PRESS);

			break;
		}
		case SDLK_4:
		{
			KeyBoardDelegates.Button4->Execute(EInputState::PRESS);

			break;
		}
		case SDLK_5:
		{
			KeyBoardDelegates.Button5->Execute(EInputState::PRESS);

			break;
		}
		case SDLK_6:
		{
			KeyBoardDelegates.Button6->Execute(EInputState::PRESS);

			break;
		}
		case SDLK_7:
		{
			KeyBoardDelegates.Button7->Execute(EInputState::PRESS);

			break;
		}
		case SDLK_8:
		{
			KeyBoardDelegates.Button8->Execute(EInputState::PRESS);

			break;
		}
		case SDLK_9:
		{
			KeyBoardDelegates.Button9->Execute(EInputState::PRESS);

			break;
		}

		case SDLK_UP:
		{
			KeyBoardDelegates.ButtonArrowUP->Execute(EInputState::PRESS);

			break;
		}
		case SDLK_DOWN:
		{
			KeyBoardDelegates.ButtonArrowDOWN->Execute(EInputState::PRESS);

			break;
		}
		case SDLK_RIGHT:
		{
			KeyBoardDelegates.ButtonArrowRIGHT->Execute(EInputState::PRESS);

			break;
		}
		case SDLK_LEFT:
		{
			KeyBoardDelegates.ButtonArrowLEFT->Execute(EInputState::PRESS);

			break;
		}

		case SDLK_DELETE:
		{
			KeyBoardDelegates.ButtonDELETE->Execute(EInputState::PRESS);

			break;
		}

		case SDLK_a:
		{
			KeyBoardDelegates.ButtonA->Execute(EInputState::PRESS);

			break;
		}
		case SDLK_b:
		{
			KeyBoardDelegates.ButtonB->Execute(EInputState::PRESS);

			break;
		}
		case SDLK_c:
		{
			KeyBoardDelegates.ButtonC->Execute(EInputState::PRESS);

			break;
		}
		case SDLK_d:
		{
			KeyBoardDelegates.ButtonD->Execute(EInputState::PRESS);

			break;
		}
		case SDLK_e:
		{
			KeyBoardDelegates.ButtonE->Execute(EInputState::PRESS);

			break;
		}
		// [...] @TODO Someday all add buttons
		case SDLK_w:
		{
			KeyBoardDelegates.ButtonW->Execute(EInputState::PRESS);

			break;
		}
		case SDLK_s:
		{
			KeyBoardDelegates.ButtonS->Execute(EInputState::PRESS);

			break;
		}

		default:
		{
			LOG_DEBUG("Unknown keyboard input found.");
		}
	}
}

void FEventHandler::InputKeyUp()
{
	switch (Event.key.keysym.sym)
	{
		case SDLK_ESCAPE:
		{
			KeyBoardDelegates.ButtonEscape->Execute(EInputState::RELEASE);

			break;
		}

		case SDLK_0:
		{
			KeyBoardDelegates.Button0->Execute(EInputState::RELEASE);

			break;
		}
		case SDLK_1:
		{
			KeyBoardDelegates.Button1->Execute(EInputState::RELEASE);

			break;
		}
		case SDLK_2:
		{
			KeyBoardDelegates.Button2->Execute(EInputState::RELEASE);

			break;
		}
		case SDLK_3:
		{
			KeyBoardDelegates.Button3->Execute(EInputState::RELEASE);

			break;
		}
		case SDLK_4:
		{
			KeyBoardDelegates.Button4->Execute(EInputState::RELEASE);

			break;
		}
		case SDLK_5:
		{
			KeyBoardDelegates.Button5->Execute(EInputState::RELEASE);

			break;
		}
		case SDLK_6:
		{
			KeyBoardDelegates.Button6->Execute(EInputState::RELEASE);

			break;
		}
		case SDLK_7:
		{
			KeyBoardDelegates.Button7->Execute(EInputState::RELEASE);

			break;
		}
		case SDLK_8:
		{
			KeyBoardDelegates.Button8->Execute(EInputState::RELEASE);

			break;
		}
		case SDLK_9:
		{
			KeyBoardDelegates.Button9->Execute(EInputState::RELEASE);

			break;
		}

		case SDLK_UP:
		{
			KeyBoardDelegates.ButtonArrowUP->Execute(EInputState::RELEASE);

			break;
		}
		case SDLK_DOWN:
		{
			KeyBoardDelegates.ButtonArrowDOWN->Execute(EInputState::RELEASE);

			break;
		}
		case SDLK_RIGHT:
		{
			KeyBoardDelegates.ButtonArrowRIGHT->Execute(EInputState::RELEASE);

			break;
		}
		case SDLK_LEFT:
		{
			KeyBoardDelegates.ButtonArrowLEFT->Execute(EInputState::RELEASE);

			break;
		}

		case SDLK_DELETE:
		{
			KeyBoardDelegates.ButtonDELETE->Execute(EInputState::RELEASE);

			break;
		}

		case SDLK_a:
		{
			KeyBoardDelegates.ButtonA->Execute(EInputState::RELEASE);

			break;
		}
		case SDLK_b:
		{
			KeyBoardDelegates.ButtonB->Execute(EInputState::RELEASE);

			break;
		}
		case SDLK_c:
		{
			KeyBoardDelegates.ButtonC->Execute(EInputState::RELEASE);

			break;
		}
		case SDLK_d:
		{
			KeyBoardDelegates.ButtonD->Execute(EInputState::RELEASE);

			break;
		}
		case SDLK_e:
		{
			KeyBoardDelegates.ButtonE->Execute(EInputState::RELEASE);

			break;
		}
		// [...] @TODO Someday all add buttons
		case SDLK_w:
		{
			KeyBoardDelegates.ButtonW->Execute(EInputState::RELEASE);

			break;
		}
		case SDLK_s:
		{
			KeyBoardDelegates.ButtonS->Execute(EInputState::RELEASE);

			break;
		}

		default:
		{
			LOG_DEBUG("Unknown keyboard input found.");
		}
	}
}

void FEventHandler::MouseMotion()
{
	if (MouseLocationLast != MouseLocationCurrent)
	{
		MouseLocationLast = MouseLocationCurrent;

		MouseDelegates.GetMouseDelegateByName("Move")->Execute(MouseLocationCurrent, EInputState::PRESS);
	}

	MouseLocationCurrent.X = Event.motion.x;
	MouseLocationCurrent.Y = Event.motion.y;
}

void FEventHandler::InputMouseDown()
{
	switch (Event.button.button)
	{
		case SDL_BUTTON_LEFT:
		{
			MouseDelegates.GetMouseDelegateByName("LeftButton")->Execute(MouseLocationCurrent, EInputState::PRESS);

			break;
		}

		case SDL_BUTTON_MIDDLE:
		{
			MouseDelegates.GetMouseDelegateByName("MiddleButton")->Execute(MouseLocationCurrent, EInputState::PRESS);

			break;
		}

		case SDL_BUTTON_RIGHT:
		{
			MouseDelegates.GetMouseDelegateByName("RightButton")->Execute(MouseLocationCurrent, EInputState::PRESS);

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
			MouseDelegates.GetMouseDelegateByName("LeftButton")->Execute(MouseLocationCurrent, EInputState::RELEASE);

			break;
		}

		case SDL_BUTTON_MIDDLE:
		{
			MouseDelegates.GetMouseDelegateByName("MiddleButton")->Execute(MouseLocationCurrent, EInputState::RELEASE);

			break;
		}

		case SDL_BUTTON_RIGHT:
		{
			MouseDelegates.GetMouseDelegateByName("RightButton")->Execute(MouseLocationCurrent, EInputState::RELEASE);

			break;
		}

		default:
		{
			LOG_DEBUG("Unknown mouse input found.");
		}
	}
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
			LOG_DEBUG("Window " << Event.window.windowID << " mouse left.");
			break;
		}

		case SDL_WINDOWEVENT_FOCUS_GAINED:
		{
			LOG_DEBUG("Window %d gained keyboard focus << " << Event.window.windowID);
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
