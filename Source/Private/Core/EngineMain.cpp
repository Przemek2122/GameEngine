// 

#include "CoreEngine.h"
#include "EngineMain.h"

FEngineManager::FEngineManager()
{
}

FEngineManager::~FEngineManager()
{
}

FEngine* FEngineManager::Get()
{
	return Engine;
}

void FEngineManager::Init(const int Argc, char* Argv[])
{
	Engine->PreInit();

	Engine->EngineInit(Argc, Argv);

	Engine->Init();

	Engine->PostInit();
}

void FEngineManager::MainLoop()
{
	while (Engine->CanContinueMainLoop())
	{
		Engine->UpdateFrameTimeStart();

		Engine->EngineTick();

		Engine->UpdateFrameTimeEnd();

		// Delay if required.
		if (Engine->IsFrameRateLimited())
		{
			const auto EngineFrameTime = Engine->GetFrameTime();
			const auto EngineFrameDelay = Engine->GetFrameDelay();

			if (EngineFrameDelay > EngineFrameTime)
			{
				SDL_Delay(EngineFrameDelay - EngineFrameTime);
			}
		}
	}
}

void FEngineManager::Exit()
{
	Engine->PreExit();

	Engine->Clean();

	delete Engine;

	std::cout << "Game engine end." << std::endl;
}
