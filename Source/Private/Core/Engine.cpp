//

#include "CoreEngine.h"

FEngine::FEngine()
	: bContinueMainLoop(true)
	, bIsEngineInitialized(true)
	, bFrameRateLimit(true)
{
	FUtil::LogInit();
}

FEngine::~FEngine()
{
	SDL_Quit();
}

void FEngine::PreInit()
{
}

void FEngine::Init(int argc, char* argv[])
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

	bIsEngineInitialized = true;
}

void FEngine::GameInit()
{
}

void FEngine::PostInit()
{
}

void FEngine::MainLoop()
{
}

bool FEngine::CanContinueMainLoop() const
{
	return bContinueMainLoop;
}

bool FEngine::IsFrameRateLimit() const
{
	return bFrameRateLimit;
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
}

bool FEngine::IsEngineInitialized() const
{
	return bIsEngineInitialized;
}
