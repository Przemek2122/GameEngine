//

#include "CoreEngine.h"

FEngine::FEngine()
	: bContinueMainLoop(true)
	, bIsEngineInitialized(false)
	, bFrameRateLimited(true)

	, FPS(0)
	, FrameDelay(0)
	, FrameStart(0)
	, FrameTime(0)
	, CounterLastFrame(0)
	, CounterCurrentFrame(SDL_GetPerformanceCounter())
	, TicksThisSecond(0)
	, Second(0)
{
	FUtil::LogInit();

	SetFrameRate(60);
}

FEngine::~FEngine()
{
	SDL_Quit();
}

void FEngine::PreInit()
{
}

void FEngine::EngineInit(int argc, char* argv[])
{
	FUtil::Info("Engine init Start");

	// Read command line flags.
	while ((++argv)[0])
	{
		if (argv[0][0] == '-')
		{
			switch (argv[0][1])
			{
			case 's':
				//Util::Info("Found s option. Enabling server.");
				break;

			default:
				FUtil::Info("Unknown option: " + (std::string)argv[0]);
				break;
			}
		}
	}

	// Initialize SDL
	const int SDLInitialized = SDL_Init(SDL_INIT_EVERYTHING);
	if (SDLInitialized == 0)
	{
		FUtil::Info("SDL Subsystems Initialised!");
	}
	else
	{
		FUtil::Error("SDL_INIT_EVERYTHING error: " + (std::string)SDL_GetError());
		exit(-2);
	}

	// Initialize SDL TTF 
	if (TTF_Init() != 0)
	{
		FUtil::Error("TTF_Init: " + (std::string)TTF_GetError());
		exit(-4);
	}

	// Initialize SDL - Load support for the OGG and MOD sample/music formats
	const int MixFlags = MIX_INIT_OGG | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_FLAC;
	const int MixInitialized = Mix_Init(MixFlags);
	if (!MixInitialized)
	{
		FUtil::Error("Mix_Init: " + (std::string)Mix_GetError());
		exit(-8);
	}

	FUtil::Info("Engine init End");

	EngineRender = CreateEngineRenderer();

	bIsEngineInitialized = true;
}

void FEngine::Init()
{
	
}

void FEngine::PostInit()
{
}

void FEngine::EngineTick()
{
	// Tick counter
	{
		size_t SystemTime = FUtil::GetSeconds();

		if (Second == SystemTime)
		{
			TicksThisSecond++;
		}
		else
		{
			EnginePostSecondTick();

			TicksThisSecond = 0;
			Second = SystemTime;
		}
	}

	Tick();
}

void FEngine::Tick()
{
	EngineRender->StartRenderTick();
}

void FEngine::EnginePostSecondTick()
{
	PostSecondTick();
}

void FEngine::PostSecondTick()
{
}

bool FEngine::CanContinueMainLoop() const
{
	return bContinueMainLoop;
}

bool FEngine::IsFrameRateLimited() const
{
	return bFrameRateLimited;
}

void FEngine::Stop()
{
	bContinueMainLoop = false;
}

void FEngine::PreExit()
{
}

void FEngine::Clean()
{
	delete EngineRender;
}

bool FEngine::IsEngineInitialized() const
{
	return bIsEngineInitialized;
}

void FEngine::UpdateFrameTimeStart()
{
	CounterLastFrame = CounterCurrentFrame;

	CounterCurrentFrame = SDL_GetPerformanceCounter();

	FrameStart = SDL_GetTicks();
}

void FEngine::UpdateFrameTimeEnd()
{
	FrameTime = SDL_GetTicks() - FrameStart;
}

uint32_t FEngine::GetFrameTime() const
{
	return FrameTime;
}

uint32_t FEngine::GetFrameDelay() const
{
	return FrameDelay;
}

void FEngine::SetFrameRate(uint32_t NewFrameRate)
{
	FPS = NewFrameRate;
	FrameDelay = 1000 / FPS;
}

int FEngine::GetFramesThisSecond() const
{
	return TicksThisSecond;
}

FEnginerRender* FEngine::CreateEngineRenderer()
{
	return new FEnginerRender();
}

FEnginerRender* FEngine::GetEngineRender() const
{
	return EngineRender;
}
