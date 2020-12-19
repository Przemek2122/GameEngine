// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Input/EventHandler.h"

FEventHandler::FEventHandler(SDL_Event InEvent)
	: Event(InEvent)
	, QuitInputDetected(false)
{
	AddInput("M_LMB"); // MOUSE- Left mouse button
	AddInput("M_RMB"); // MOUSE- Right mouse button
	AddInput("M_MID"); // MOUSE- Middle mouse button
	
	AddInput("K_A"); // KEYBOARD - A
	AddInput("K_B"); // KEYBOARD - B
	AddInput("K_C"); // KEYBOARD - C
	AddInput("K_D"); // KEYBOARD - D
	
	AddInput("K_1"); // KEYBOARD - Number - 1
	AddInput("K_2"); // KEYBOARD - Number - 2
	AddInput("K_3"); // KEYBOARD - Number - 3
	AddInput("K_4"); // KEYBOARD - Number - 4
	AddInput("K_5"); // KEYBOARD - Number - 5
	AddInput("K_6"); // KEYBOARD - Number - 6
	AddInput("K_7"); // KEYBOARD - Number - 7
	AddInput("K_8"); // KEYBOARD - Number - 8
	AddInput("K_9"); // KEYBOARD - Number - 9
	AddInput("K_0"); // KEYBOARD - Number - 0
}

FEventHandler::~FEventHandler()
{
}

void FEventHandler::HandleEvents()
{
	while (SDL_PollEvent(&Event)) 
	{
		switch (Event.type)
		{
		// Mouse movement X & Y
		case SDL_MOUSEMOTION:
			{
				MouseLocationLast = MouseLocationCurrent;
				
				MouseLocationCurrent.X = Event.motion.x;
				MouseLocationCurrent.Y = Event.motion.y;
					
				break;
			}

		// Mouse buttons
		case SDL_MOUSEBUTTONDOWN: // Press Mouse
			switch (Event.button.button)
			{
			case SDL_BUTTON_LEFT:
				{
					InputMap["M_LMB"] = true;
					
					break;
				}

			case SDL_BUTTON_RIGHT:
				{
					InputMap["M_RMB"] = true;
					
					break;
				}

			case SDL_BUTTON_MIDDLE:
				{
					InputMap["M_MID"] = true;
					
					break;
				}
				
			default:
				LOG_DEBUG("Unknown mouse input found.");
				break;
			}
			
		// Keyboard
		switch (Event.key.keysym.sym)
			{
			case SDLK_1:
				{
					InputMap["K_1"] = true;

					break;
				}
			case SDLK_2:
				{
					InputMap["K_2"] = true;

					break;
				}
			case SDLK_3:
				{
					InputMap["K_3"] = true;

					break;
				}
			case SDLK_4:
				{
					InputMap["K_4"] = true;

					break;
				}
			
			default:
				{
					LOG_DEBUG("Unknown keyboard input found.");
					break;
				}
			}

		case SDL_QUIT:
			{
				QuitInputDetected = false;
				
				LOG_DEBUG("Unknown mouse input found.");
				
				break;
			}

		default:
			LOG_DEBUG("Unknown input found.");
			break;
		}
	}
	
	/*
	while (SDL_PollEvent(&Event)) 
	{
		switch (Event.type)
		{

		case SDL_MOUSEMOTION: // Mouse movement X & Y
			Mouse::SetMouse(event.motion.x, event.motion.y);
			break;

		case SDL_MOUSEBUTTONDOWN: // Press Mouse
			switch (event.button.button) {
			case SDL_BUTTON_LEFT:
				Mouse::SetLMB(true);
				break;
			case SDL_BUTTON_RIGHT:
				Mouse::SetRMB(true);
				break;

			default:
				break;
			}
			break;

		case SDL_MOUSEBUTTONUP: // Release Mouse
			switch (event.button.button) {
			case SDL_BUTTON_LEFT:
				Mouse::SetLMB(false);
				break;
			case SDL_BUTTON_RIGHT:
				Mouse::SetRMB(false);
				break;

			default:
				break;
			}
			break;

		case SDL_KEYDOWN: // Button press
			switch (event.key.keysym.sym) {
			case SDLK_UP:
				Keyboard::SetArrowUP(true);
				break;
			case SDLK_DOWN:
				Keyboard::SetArrowDown(true);
				break;
			case SDLK_LEFT:
				Keyboard::SetArrowLeft(true);
				break;
			case SDLK_RIGHT:
				Keyboard::SetArrowRight(true);
				break;

			case SDLK_w:
				Keyboard::SetKeyW(true);
				break;
			case SDLK_s:
				Keyboard::SetKeyS(true);
				break;
			case SDLK_a:
				Keyboard::SetKeyA(true);
				break;
			case SDLK_d:
				Keyboard::SetKeyD(true);
				break;

			case SDLK_r:
				Keyboard::SetKeyR(true);
				break;
			case SDLK_h:
				Keyboard::SetKeyH(true);
				break;

			case SDLK_0:
				Keyboard::SetKey_0(true);
				break;
			case SDLK_1:
				Keyboard::SetKey_1(true);
				break;
			case SDLK_2:
				Keyboard::SetKey_2(true);
				break;
			case SDLK_3:
				Keyboard::SetKey_3(true);
				break;
			case SDLK_4:
				Keyboard::SetKey_4(true);
				break;
			case SDLK_5:
				Keyboard::SetKey_5(true);
				break;
			case SDLK_6:
				Keyboard::SetKey_6(true);
				break;
			case SDLK_7:
				Keyboard::SetKey_7(true);
				break;
			case SDLK_8:
				Keyboard::SetKey_8(true);
				break;
			case SDLK_9:
				Keyboard::SetKey_9(true);
				break;
			}
			break;

		case SDL_KEYUP: // Button release
			switch (event.key.keysym.sym) {
			case SDLK_UP:
				Keyboard::SetArrowUP(false);
				break;
			case SDLK_DOWN:
				Keyboard::SetArrowDown(false);
				break;
			case SDLK_LEFT:
				Keyboard::SetArrowLeft(false);
				break;
			case SDLK_RIGHT:
				Keyboard::SetArrowRight(false);
				break;

			case SDLK_w:
				Keyboard::SetKeyW(false);
				break;
			case SDLK_s:
				Keyboard::SetKeyS(false);
				break;
			case SDLK_a:
				Keyboard::SetKeyA(false);
				break;
			case SDLK_d:
				Keyboard::SetKeyD(false);
				break;

			case SDLK_r:
				Keyboard::SetKeyR(false);
				break;
			case SDLK_h:
				Keyboard::SetKeyH(false);
				break;

			case SDLK_0:
				Keyboard::SetKey_0(false);
				break;
			case SDLK_1:
				Keyboard::SetKey_1(false);
				break;
			case SDLK_2:
				Keyboard::SetKey_2(false);
				break;
			case SDLK_3:
				Keyboard::SetKey_3(false);
				break;
			case SDLK_4:
				Keyboard::SetKey_4(false);
				break;
			case SDLK_5:
				Keyboard::SetKey_5(false);
				break;
			case SDLK_6:
				Keyboard::SetKey_6(false);
				break;
			case SDLK_7:
				Keyboard::SetKey_7(false);
				break;
			case SDLK_8:
				Keyboard::SetKey_8(false);
				break;
			case SDLK_9:
				Keyboard::SetKey_9(false);
				break;
			}
			break;

		case SDL_QUIT:
			running = false;
			break;

		default:
			break;
		}
	}
	*/
}

void FEventHandler::ResetAllButtons()
{
	InputMap.SetAll(false);
}

bool FEventHandler::HasInput(std::string InputName)
{
	return InputMap.HasKey(InputName);
}

bool FEventHandler::GetInput(std::string InputName)
{
	return InputMap[static_cast<std::string>(InputName)];
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

void FEventHandler::AddInput(std::string InputName)
{
	bool Default = false;
	
	InputMap.Emplace(InputName, Default);
}

void FEventHandler::RemoveInput(std::string InputName)
{
	if (InputMap.Remove(InputName))
	{
		ENSURE("Not removed - not found.");
	}
}
