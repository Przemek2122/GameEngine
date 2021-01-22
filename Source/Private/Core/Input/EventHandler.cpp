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
	ResetAllButtons();
	
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
			case SDLK_5:
				{
					InputMap["K_5"] = true;

					break;
				}
			case SDLK_6:
				{
					InputMap["K_6"] = true;

					break;
				}
			case SDLK_7:
				{
					InputMap["K_7"] = true;

					break;
				}
			case SDLK_8:
				{
					InputMap["K_8"] = true;

					break;
				}
			case SDLK_9:
				{
					InputMap["K_9"] = true;

					break;
				}
			case SDLK_0:
				{
					InputMap["K_0"] = true;

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
