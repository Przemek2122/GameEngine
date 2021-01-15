//

#include "CoreEngine.h"
#include "Input/EventHandler.h"


FEngine::FEngine()
	: bContinueMainLoop(true)
	, bFrameRateLimited(true)
	, bIsEngineInitialized(false)

	, FrameRate(0)
	, FrameDelay(0)
	, FrameStart(0)
	, FrameTime(0)
	, CounterLastFrame(0)
	, TicksThisSecond(0)
	, Second(0)
	, EngineRender(CreateEngineRenderer())
	, EventHandler(CreateEventHandler())
{
	FUtil::LogInit();

	SetFrameRate(60);
}

FEngine::~FEngine()
{
	LOG_INFO("Engine finish.");
	
	SDL_Quit();
}

void FEngine::EngineInit(int Argc, char* Argv[])
{
#if defined(__DATE__) && defined(__TIME__)
		LOG_INFO("Engine init start compiled: " << __DATE__ << " " <<__TIME__);
#else
		LOG_INFO("Engine init start.");
#endif
	
	// Read command line flags.
	while (Argc--)
	{
		if (Argc == 0)
		{
			LaunchExePath = Argv[Argc];

			LOG_INFO("Found launch exe path [" << Argc << "] = " << Argv[Argc]);
		}
		else
		{
			LaunchParameters.Push(Argv[Argc]);
			
			LOG_INFO("Found param [" << Argc << "] = " << Argv[Argc]);
		}
	}

	// Initialize SDL
	const auto SdlInitialized = SDL_Init(SDL_INIT_EVERYTHING);
	if (SdlInitialized == 0)
	{
		LOG_INFO("SDL Subsystems Initialised!");
	}
	else
	{
		LOG_ERROR("SDL_INIT_EVERYTHING error: " << SDL_GetError());

		exit(-2);
	}

	// Initialize SDL TTF 
	if (TTF_Init() != 0)
	{
		LOG_ERROR("TTF_Init: " << TTF_GetError());

		exit(-4);
	}

	// Initialize SDL - Load support for the OGG and MOD sample/music formats
	const auto MixFlags = MIX_INIT_OGG | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_FLAC;
	const auto MixInitialized = Mix_Init(MixFlags);
	if (!MixInitialized)
	{
		LOG_ERROR("Mix_Init: " << Mix_GetError());

		exit(-8);
	}

	LOG_INFO("Engine init End");

	bIsEngineInitialized = true;
}

void FEngine::EngineTick()
{
	// Tick counter
	{
		const auto SystemTime = FUtil::GetSeconds();

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

	EventHandler->HandleEvents();

	Tick();

	EngineRender->Tick();
}

void FEngine::EnginePostSecondTick()
{
	PostSecondTick();
}

void FEngine::PreInit()
{
}

void FEngine::Init()
{
	
}

void FEngine::PostInit()
{
}

void FEngine::Tick()
{
	
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

void FEngine::SetFrameRate(const uint32_t NewFrameRate)
{
	FrameRate = NewFrameRate;
	FrameDelay = 1000 / FrameRate;
}

int FEngine::GetFramesThisSecond() const
{
	return TicksThisSecond;
}

FEngineRender* FEngine::CreateEngineRenderer() const
{
	return new FEngineRender();
}

FEventHandler* FEngine::GetEventHandler() const
{
	return EventHandler;
}

FEventHandler* FEngine::CreateEventHandler() const
{
	return new FEventHandler(SdlEvent);
}

FEngineRender* FEngine::GetEngineRender() const
{
	return EngineRender;
}
