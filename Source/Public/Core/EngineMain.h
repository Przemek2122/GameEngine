// GameEngine.h Main engine file

#pragma once

#include "CoreEngine.h"
#include "Engine.h"
#include "Includes/Statics.h"

template<class FEngineClass = FEngine>
void RunEngine(int argc, char* argv[])
{
	// Init
	{
		std::cout << "Game engine initializing ..." << std::endl;

		Engine = new FEngineClass();

		Engine->PreInit();

		Engine->EngineInit(argc, argv);

		Engine->Init();

		Engine->PostInit();
	}

	// Main loop
	{
		while (Engine->CanContinueMainLoop())
		{
			Engine->UpdateFrameTimeStart();

			Engine->EngineTick();

			Engine->UpdateFrameTimeEnd();

			if (Engine->IsFrameRateLimited())
			{
				const uint32_t EngineFrameTime = Engine->GetFrameTime();
				const uint32_t EngineFrameDelay = Engine->GetFrameDelay();

				if (EngineFrameDelay > EngineFrameTime)
				{
					SDL_Delay(EngineFrameDelay - EngineFrameTime);
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
