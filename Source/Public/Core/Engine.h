// 

#pragma once

#include "CoreMinimal.h"
class FEngineManager;

class FEngine
{
friend FEngineManager;
	
protected:
	FEngine();
	virtual ~FEngine();

private:
	/** Called before tick. Once. */
	void EngineInit(int Argc, char* Argv[]);
	
	/** Is inside of loop. Runs until Exit() is called. */
	void EngineTick();

	/** Called once a second. */
	void EnginePostSecondTick();
public:
	/** First init ever called. */
	virtual void PreInit();

	/** Init (SDL, Engine stuff). */
	virtual void Init();

	/** Third init function. */
	virtual void PostInit();

	/** To be sub-project overriden. Called each frame */
	virtual void Tick();

	/** To be sub-project overriden. Called every second */
	virtual void PostSecondTick();

	/** MainLoop() runs until this return false. */
	_NODISCARD virtual bool CanContinueMainLoop() const;

	/** True if frame rate limit is enabled. */
	_NODISCARD virtual bool IsFrameRateLimited() const;

	/** Call to stop main loop. (Exit engine) */
	virtual void Stop();

	/** Called when main loops stop but before destructor. */
	virtual void PreExit();

	/** Clean up memory. (Remember to call parent! Otherwise you will leak memory.) */
	virtual void Clean();

	/** @returns true if Init() has finished */
	_NODISCARD bool IsEngineInitialized() const;

private:
	bool bContinueMainLoop;

protected:
	bool bFrameRateLimited;
	bool bIsEngineInitialized;

public:
	virtual void UpdateFrameTimeStart();
	virtual void UpdateFrameTimeEnd();

	_NODISCARD uint32_t GetFrameTime() const;
	_NODISCARD uint32_t GetFrameDelay() const;

	// Use to set engine frame rate - ticks per second
	virtual void SetFrameRate(const uint32_t NewFrameRate);

	_NODISCARD int GetFramesThisSecond() const;

protected:
	// Framerate per second / ticks per second
	uint32_t FrameRate;
	// Cached per frame delay for example 60 FPS will be 60 / 1000 = 16
	uint32_t FrameDelay;

	// Time ms of frame start
	uint32_t FrameStart;
	// Time ms of frame end
	uint32_t FrameTime;

	uint64_t CounterLastFrame;
	uint64_t CounterCurrentFrame = SDL_GetPerformanceCounter();

private:
	int TicksThisSecond;
	size_t Second;

public:
	/** @Returns engine render class (used for managing windows) */
	_NODISCARD FEngineRender* GetEngineRender() const;

	/** Use this if you changed to your own. Will return casted. */
	template<typename TRenderClass>
	TRenderClass* GetEngineRender() const
	{
		return static_cast<TRenderClass>(GetEngineRender());
	}

protected:
	FEngineRender* EngineRender;

	virtual FEngineRender* CreateEngineRenderer();






	static SDL_Event Event;
	//static AssetsManager* Assets;


};