#include <Engine.PCH.h>
#include "Engine.h"

FEngine::FEngine()
	: bContinueMainLoop(true)
	, bFrameRateLimit(true)
{
}

FEngine::~FEngine()
{
}

void FEngine::PreInit()
{
}

void FEngine::Init(int argc, char* argv[])
{
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
				//Util::Info("Unknown option: " + (std::string)argv[0]);
				break;
			}
		}
	}
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
