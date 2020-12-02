// GameEngine.h Main engine file

#pragma once

#include <Engine.PCH.h>
#include "Engine.h"

static FEngine* Engine = nullptr;

template<class FEngineClass = FEngine>
void RunEngine(int argc, char* argv[])
{
	// Init
	{
		std::cout << "Game engine start." << std::endl;

		Engine = new FEngineClass();

		Engine->PreInit();

		Engine->Init(argc, argv);
	}

	// Main loop
	{
		// FPS limit
		const uint32_t FPS = 60;
		const uint32_t FrameDelay = 1000 / FPS;

		uint32_t FrameStart;
		uint32_t FrameTime;

		// Deltatime
		uint64_t CounterLastFrame = 0;
		uint64_t CounterCurrentFrame = SDL_GetPerformanceCounter();

		while (Engine->CanContinueMainLoop())
		{
			// Deltatime
			CounterLastFrame = CounterCurrentFrame;
			CounterCurrentFrame = SDL_GetPerformanceCounter();

			FrameStart = SDL_GetTicks();

			Engine->MainLoop();

			if (Engine->IsFrameRateLimit())
			{
				FrameTime = SDL_GetTicks() - FrameStart;

				if (FrameDelay > FrameTime)
				{
					SDL_Delay(FrameDelay - FrameTime);
				}
			}
		}
	}

	// Exit
	{
		Engine->PreExit();

		Engine->Clean();

		delete Engine;

		std::cout << "Game engine end." << std::endl;
	}
}
