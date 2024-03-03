// Created by Przemys³aw Wiewióra 2020-2022 https://github.com/Przemek2122/GameEngine

#include "CoreEngine.h"
#include "Input/EventHandler.h"

#if ENGINE_TESTS_ALLOW_ANY
#include "Test/TestManager.h"

#include "Test/TestDelegate.h"
#include "Test/TestTypes.h"
#endif

#include "Assets/Assets/FontAsset.h"
#include "Interfaces/CoreLoop/TickInterface.h"
#include "Interfaces/CoreLoop/RenderInterface.h"
#include "Renderer/Map/Mapmanager.h"

FEngine::FEngine()
	: bFrameRateLimited(true)
	, bIsEngineInitialized(false)
	, FrameRate(0)
	, FrameDelay(0)
	, FrameStart(0)
	, FrameTime(0)
	, CounterLastFrame(0)
	, CounterCurrentFrame(SDL_GetPerformanceCounter())
	, bContinueMainLoop(true)
	, TicksThisSecond(0)
	, Second(0)
	, EngineRender(nullptr)
	, EventHandler(nullptr)
	, AssetsManager(nullptr)
#if ENGINE_TESTS_ALLOW_ANY
	, TestManager(nullptr)
#endif
{
	FUtil::LogInit();
}

FEngine::~FEngine()
{
	LOG_INFO("GEngine finish (is being destroyed now).");

	TTF_Quit();
	SDL_Quit();
}

void FEngine::EngineInit(int Argc, char* Argv[])
{
#if defined(__DATE__) && defined(__TIME__)
	LOG_INFO("GEngine init start compiled: " << __DATE__ << " " <<__TIME__);
#else
	LOG_INFO("GEngine init start.");
#endif

	SetFrameRate(60);
	
	// Read command line flags.
	while (Argc--)
	{
		if (Argc == 0)
		{
			LaunchFullPath = Argv[Argc];

			LOG_INFO("Found launch exe path [" << Argc << "] = " << Argv[Argc]);
		}
		else
		{
			LaunchParameters.Push(Argv[Argc]);
			
			LOG_INFO("Found param [" << Argc << "] = " << Argv[Argc]);
		}
	}

	// We always need correct directory.
	if (ENSURE_VALID(!LaunchFullPath.empty()))
	{
		LaunchRelativePath = LaunchFullPath.substr(0, LaunchFullPath.find_last_of('\\'));
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

	/**
	 * @TODO HACK
	 * https://stackoverflow.com/questions/40312553/sdl2-crashes-on-window-resize
	 * Workarround for crash. Should be changed in feature but it does not matter for now.
	 */
	SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");

	EngineRender = CreateEngineRenderer();
	EventHandler = CreateEventHandler();
	AssetsManager = CreateAssetsManager();
#if ENGINE_TESTS_ALLOW_ANY
	TestManager = CreateTestManager();
#endif

#if ENGINE_TESTS_ALLOW_ANY && ENGINE_TESTS_RUN
	TestManager->SpawnTestCaseByClass<FTestTypes>();
	TestManager->SpawnTestCaseByClass<FTestDelegate>();
#endif

	AssetsManager->AddAsset<FFontAsset>("OpenSans", R"(Assets\Fonts\OpenSans\OpenSans-Regular.ttf)");

	LOG_INFO("GEngine init End");

	bIsEngineInitialized = true;
}

void FEngine::EngineTick()
{
	UpdateFramerateCounter();

	// Tick functions for next tick
	if (FunctionsToCallOnStartOfNextTick.IsBound())
	{
		FunctionsToCallOnStartOfNextTick.Execute();

		FunctionsToCallOnStartOfNextTick.UnBindAll();
	}

	// Wait for Render thread.
	// We need to do this to avoid changing data when render is not finished
	//while (!EngineRender->IsRenderTickFinished())
	//{
	//	SDL_Delay(1);
	//}

	EventHandler->HandleEvents();

	if (EventHandler->QuitInputDetected())
	{
		GEngine->RequestExit();
	}

	// Tick objects registered with TickInterface
	TickingObjectsDelegate.Execute(DeltaTimeFloat);

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

void FEngine::RequestExit()
{
	bContinueMainLoop = false;
}

void FEngine::PreExit()
{
}

void FEngine::Clean()
{
	delete EngineRender;
	delete EventHandler;
	delete AssetsManager;

#if ENGINE_TESTS_ALLOW_ANY
	delete TestManager;
#endif
}

bool FEngine::IsEngineInitialized() const
{
	return bIsEngineInitialized;
}

void FEngine::UpdateFramerateCounter()
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

double FEngine::GetMaxDeltaTime() const
{
	return 0.3;
}

void FEngine::SetDeltaTime(const double &InDeltaTime)
{
	const auto LocalDeltaTimeMax = GetMaxDeltaTime();
	
	if (InDeltaTime < LocalDeltaTimeMax)
	{
		DeltaTimeDouble = InDeltaTime;
		DeltaTimeFloat = static_cast<float>(InDeltaTime);	
	}
	else
	{
		DeltaTimeDouble = LocalDeltaTimeMax;
		DeltaTimeFloat = static_cast<float>(LocalDeltaTimeMax);
	}
}

FEngineRender* FEngine::CreateEngineRenderer() const
{
	return new FEngineRender();
}

const std::string& FEngine::GetLaunchFullPath() const
{
	return LaunchFullPath;
}

const std::string& FEngine::GetLaunchRelativePath() const
{
	return LaunchRelativePath;
}

void FEngine::AddLambdaToCallOnStartOfNextTick(FFunctorLambda<void>& Function)
{
	FunctionsToCallOnStartOfNextTick.BindLambda(Function);
}

FDelegate<void>& FEngine::GetFunctionsToCallOnStartOfNextTick()
{
	return FunctionsToCallOnStartOfNextTick;
}

FEventHandler* FEngine::GetEventHandler() const
{
#if _DEBUG
		ENSURE_VALID(EventHandler != nullptr);
#endif
		
	return EventHandler;
}

FAssetsManager* FEngine::GetAssetsManager() const
{
	return AssetsManager;
}

void FEngine::RegisterTickingObject(FTickInterface* TickInterface)
{
	TickingObjectsDelegate.BindObject(TickInterface, &FTickInterface::Tick);
}

void FEngine::UnRegisterTickingObject(FTickInterface* TickInterface)
{
	TickingObjectsDelegate.UnBindObject(TickInterface, &FTickInterface::Tick);
}

FEventHandler* FEngine::CreateEventHandler() const
{
	return new FEventHandler(SdlEvent);
}

FAssetsManager* FEngine::CreateAssetsManager() const
{
	return new FAssetsManager;
}

#if ENGINE_TESTS_ALLOW_ANY
FTestManager* FEngine::CreateTestManager() const
{
	return new FTestManager;
}
#endif

FEngineRender* FEngine::GetEngineRender() const
{
#if _DEBUG
		ENSURE_VALID(EngineRender != nullptr);
#endif
	
	return EngineRender;
}
