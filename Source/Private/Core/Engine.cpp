//

#include "Engine.h"
#include <Engine.PCH.h>

FEngine::FEngine()
	: bContinueMainLoop(true)
	, bFrameRateLimit(true)
{
	//Window = nullptr;
	//Renderer = nullptr;
}

FEngine::~FEngine()
{
}

void FEngine::PreInit()
{
}

void FEngine::Init(int argc, char* argv[])
{
	// Enable log thread
	FUtil::LogInit();

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



	FUtil::Info("Engine init End");
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
