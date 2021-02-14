// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Input/EventHandler.h"

FEventHandler::FEventHandler(SDL_Event InEvent)
	: Event(InEvent)
	, bQuitInputDetected(false)
{
	AddPrimaryInput("M_LMB");	// MOUSE- Left mouse button
	AddPrimaryInput("M_RMB");	// MOUSE- Right mouse button
	AddPrimaryInput("M_MID");	// MOUSE- Middle mouse button
	
	AddPrimaryInput("K_A");		// KEYBOARD - A
	AddPrimaryInput("K_B");		// KEYBOARD - B
	AddPrimaryInput("K_C");		// KEYBOARD - C
	AddPrimaryInput("K_D");		// KEYBOARD - D
	
	AddPrimaryInput("K_1");		// KEYBOARD - Number - 1
	AddPrimaryInput("K_2");		// KEYBOARD - Number - 2
	AddPrimaryInput("K_3");		// KEYBOARD - Number - 3
	AddPrimaryInput("K_4");		// KEYBOARD - Number - 4
	AddPrimaryInput("K_5");		// KEYBOARD - Number - 5
	AddPrimaryInput("K_6");		// KEYBOARD - Number - 6
	AddPrimaryInput("K_7");		// KEYBOARD - Number - 7
	AddPrimaryInput("K_8");		// KEYBOARD - Number - 8
	AddPrimaryInput("K_9");		// KEYBOARD - Number - 9
	AddPrimaryInput("K_0");		// KEYBOARD - Number - 0
}

FEventHandler::~FEventHandler()
{
}

void FEventHandler::HandleEvents()
{
	ResetAllButtons();

	// @TODO SDLK_1 to '1' - Performance Improvement
	
	while (SDL_PollEvent(&Event)) 
	{
		const auto EventType = Event.type;
		
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
				switch (Event.window.event)
				{
			        case SDL_WINDOWEVENT_SHOWN:
					{
			            SDL_Log("Window %d shown", Event.window.windowID);
			            break;
					}
					
			        case SDL_WINDOWEVENT_HIDDEN:
					{
			            SDL_Log("Window %d hidden", Event.window.windowID);
			            break;
					}
					
			        case SDL_WINDOWEVENT_EXPOSED:
					{
			            SDL_Log("Window %d exposed", Event.window.windowID);
			            break;
					}
					
			        case SDL_WINDOWEVENT_MOVED:
					{
			            SDL_Log("Window %d moved to %d,%d",
			                    Event.window.windowID, Event.window.data1,
			                    Event.window.data2);
			            break;
					}
					
			        case SDL_WINDOWEVENT_RESIZED:
					{
			            SDL_Log("Window %d resized to %dx%d",
			                    Event.window.windowID, Event.window.data1,
			                    Event.window.data2);
			            break;
					}
					
			        case SDL_WINDOWEVENT_SIZE_CHANGED:
					{
			            SDL_Log("Window %d size changed to %dx%d",
			                    Event.window.windowID, Event.window.data1,
			                    Event.window.data2);
			            break;
					}
					
			        case SDL_WINDOWEVENT_MINIMIZED:
					{
			            SDL_Log("Window %d minimized", Event.window.windowID);
			            break;
					}
					
			        case SDL_WINDOWEVENT_MAXIMIZED:
					{
			            SDL_Log("Window %d maximized", Event.window.windowID);
			            break;
					}
					
			        case SDL_WINDOWEVENT_RESTORED:
					{
			            SDL_Log("Window %d restored", Event.window.windowID);
			            break;
					}
					
			        case SDL_WINDOWEVENT_ENTER:
					{
			            SDL_Log("Mouse entered window %d",
			                    Event.window.windowID);
			            break;
					}
					
			        case SDL_WINDOWEVENT_LEAVE:
					{
			            SDL_Log("Mouse left window %d", Event.window.windowID);
			            break;
					}
					
			        case SDL_WINDOWEVENT_FOCUS_GAINED:
					{
			            SDL_Log("Window %d gained keyboard focus",
			                    Event.window.windowID);
			            break;
					}
					
			        case SDL_WINDOWEVENT_FOCUS_LOST:
					{
			            SDL_Log("Window %d lost keyboard focus",
			                    Event.window.windowID);
			            break;
					}
					
			        case SDL_WINDOWEVENT_CLOSE:
					{
			            SDL_Log("Window %d closed", Event.window.windowID);
			            break;
					}
					
			        case SDL_WINDOWEVENT_TAKE_FOCUS:
					{
			            SDL_Log("Window %d is offered a focus", Event.window.windowID);
			            break;
					}
					
			        case SDL_WINDOWEVENT_HIT_TEST:
					{
			            SDL_Log("Window %d has a special hit test", Event.window.windowID);
			            break;
					}
					
			        default:
					{
			            SDL_Log("Window %d got unknown event %d", Event.window.windowID, Event.window.event);
					}
				}

				break;
			}
			
			/** Keyboard */
			case SDL_KEYDOWN:
			{
				switch (Event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
					{
						bQuitInputDetected = false;
							
						LOG_DEBUG("Quit input.");
						
						break;
					}
					
					case SDLK_1:
					{
						PrimaryInputMap["K_1"] = true;

						break;
					}
					case SDLK_2:
					{
						PrimaryInputMap["K_2"] = true;

						break;
					}
					case SDLK_3:
					{
						PrimaryInputMap["K_3"] = true;

						break;
					}
					case SDLK_4:
					{
						PrimaryInputMap["K_4"] = true;

						break;
					}
					case SDLK_5:
					{
						PrimaryInputMap["K_5"] = true;

						break;
					}
					case SDLK_6:
					{
						PrimaryInputMap["K_6"] = true;

						break;
					}
					case SDLK_7:
					{
						PrimaryInputMap["K_7"] = true;

						break;
					}
					case SDLK_8:
					{
						PrimaryInputMap["K_8"] = true;

						break;
					}
					case SDLK_9:
					{
						PrimaryInputMap["K_9"] = true;

						break;
					}
					case SDLK_0:
					{
						PrimaryInputMap["K_0"] = true;

						break;
					}
					
					default:
					{
						LOG_DEBUG("Unknown keyboard input found.");
					}
				}

				break;
			}
			
			/** Mouse movement X & Y */
			case SDL_MOUSEMOTION:
			{
				MouseLocationLast = MouseLocationCurrent;
					
				MouseLocationCurrent.X = Event.motion.x;
				MouseLocationCurrent.Y = Event.motion.y;
						
				break;
			}

			/** Mouse buttons */
			case SDL_MOUSEBUTTONDOWN:
			{
				switch (Event.button.button)
				{
					case SDL_BUTTON_LEFT:
					{
						PrimaryInputMap["M_LMB"] = true;
							
						break;
					}

					case SDL_BUTTON_RIGHT:
					{
						PrimaryInputMap["M_RMB"] = true;
							
						break;
					}

					case SDL_BUTTON_MIDDLE:
					{
						PrimaryInputMap["M_MID"] = true;
							
						break;
					}
						
					default:
					{
						LOG_DEBUG("Unknown mouse input found.");
					}
				}

				break;
			}

			default:
			{
				LOG_DEBUG("Unknown input found. Input: " << Event.type);
			}
		}
	}
}

void FEventHandler::ResetAllButtons()
{
	PrimaryInputMap.SetAll(false);
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

bool FEventHandler::HasPrimaryInput(std::string InputName)
{
	return PrimaryInputMap.HasKey(InputName);
}

bool FEventHandler::GetPrimaryInput(std::string InputName)
{
	return PrimaryInputMap[InputName];
}

void FEventHandler::AddPrimaryInput(const std::string& InPrimaryName)
{
	PrimaryInputMap.Emplace(InPrimaryName, false);
}

void FEventHandler::RemovePrimaryInput(const std::string& InPrimaryName)
{
	if (PrimaryInputMap.Remove(InPrimaryName))
	{
#ifdef _DEBUG
		ENSURE_VALID_MESSAGE(false, "Not removed - not found.");
#endif
	}
}

void FEventHandler::RemoveSecondaryInput(const std::string& InSecondaryName)
{
	const bool bIsRemoved = SecondaryInputMap.Remove(InSecondaryName);

#ifdef _DEBUG
		ENSURE_VALID_MESSAGE(bIsRemoved > 0, "Not removed - not found.");
#endif
}

void FEventHandler::SetSecondaryInput(const std::string& InSecondaryName, const std::string& InPrimaryName)
{
	if (PrimaryInputMap.ContainsKey(InPrimaryName))
	{
		if (SecondaryInputMap.ContainsValue(InSecondaryName))
		{
			SecondaryInputMap.Remove(InSecondaryName);
		}
		
		SecondaryInputMap.InsertOrAssign(InSecondaryName, InPrimaryName);
	}
#ifdef _DEBUG
	else
	{
		ENSURE_VALID_MESSAGE(false, "Missing primary key.");
	}
#endif
}

bool FEventHandler::HasSecondaryInput(const std::string& InputName)
{
	if (SecondaryInputMap.ContainsKey(InputName))
	{
		if (PrimaryInputMap.ContainsKey(SecondaryInputMap.FindValueByKey(InputName)))
		{
			return true;
		}
	}

	return false;
}

bool FEventHandler::GetSecondaryInput(const std::string& InputName)
{
	if (SecondaryInputMap.ContainsKey(InputName))
	{
		const std::string SecondaryValue = SecondaryInputMap.FindValueByKey(InputName);
		
		if (PrimaryInputMap.ContainsKey(SecondaryValue))
		{
			return PrimaryInputMap.FindValueByKey(SecondaryValue);
		}
	}

	ENSURE_VALID_MESSAGE(false, "FEventHandler::GetSecondaryInput(): Unable to find input.");

	return false;
}

bool FEventHandler::QuitInputDetected() const
{
	return bQuitInputDetected;
}
