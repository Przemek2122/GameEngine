// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Input/EventHandler.h"

void FMouseClickDelegateWrapper::Execute(const FVector2D<int>& Location)
{
	if (!bWasSentAlready)
	{
		bWasSentAlready = true;

		OnMouseClicked.Execute(Location);
	}
}

void FMouseClickDelegateWrapper::Reset()
{
	bWasSentAlready = false;
}

FEventHandler::FEventHandler(const SDL_Event& InEvent)
	: Event(InEvent)
	, bQuitInputDetected(false)
{
	AddPrimaryInput("M_LMB_P");	// MOUSE- Left mouse button pressed
	AddPrimaryInput("M_RMB_P");	// MOUSE- Right mouse button pressed
	AddPrimaryInput("M_MID_P");	// MOUSE- Middle mouse button pressed
	
	AddPrimaryInput("M_LMB_R");	// MOUSE- Left mouse button released
	AddPrimaryInput("M_RMB_R");	// MOUSE- Right mouse button released
	AddPrimaryInput("M_MID_R");	// MOUSE- Middle mouse button released
	
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
			        	LOG_DEBUG("Window " << Event.window.windowID << " has a special hit test " );
			            break;
					}
					
			        default:
					{
			        	LOG_DEBUG("Window " << Event.window.windowID << " got unknown event" << Event.window.event);
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
				if (MouseLocationLast != MouseLocationCurrent)
				{
					MouseLocationLast = MouseLocationCurrent;

					OnMouseMoved.Execute(MouseLocationCurrent);
				}

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
						PrimaryInputMap["M_LMB_P"] = true;

							
						break;
					}

					case SDL_BUTTON_RIGHT:
					{
						PrimaryInputMap["M_RMB_P"] = true;
							
						break;
					}

					case SDL_BUTTON_MIDDLE:
					{
						PrimaryInputMap["M_MID_P"] = true;
							
						break;
					}
						
					default:
					{
						LOG_DEBUG("Unknown mouse input found.");
					}
				}

				break;
			}
			
			case SDL_MOUSEBUTTONUP:
			{
				switch (Event.button.button)
				{
					case SDL_BUTTON_LEFT:
					{
						PrimaryInputMap["M_LMB_R"] = true;

						MouseLeftClickDelegate.Execute(MouseLocationCurrent);
							
						break;
					}

					case SDL_BUTTON_RIGHT:
					{
						PrimaryInputMap["M_RMB_R"] = true;

						MouseRightClickDelegate.Execute(MouseLocationCurrent);
							
						break;
					}

					case SDL_BUTTON_MIDDLE:
					{
						PrimaryInputMap["M_MID_R"] = true;
							
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

bool FEventHandler::HasPrimaryInput(const std::string& InputName)
{
	return PrimaryInputMap.HasKey(InputName);
}

auto FEventHandler::GetPrimaryInput(const std::string& InputName) -> bool
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
		ENSURE_VALID(false);
#endif
	}
}

void FEventHandler::RemoveSecondaryInput(const std::string& InSecondaryName)
{
	const bool bIsRemoved = SecondaryInputMap.Remove(InSecondaryName);

#ifdef _DEBUG
	ENSURE_VALID(bIsRemoved);
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
		ENSURE_VALID(false);
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

	ENSURE_VALID(false);

	return false;
}

bool FEventHandler::QuitInputDetected() const
{
	return bQuitInputDetected;
}
