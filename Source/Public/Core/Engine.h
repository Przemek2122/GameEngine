// 

#pragma once

#include "CoreMinimal.h"

class FEngine
{
public:
	FEngine();
	virtual ~FEngine();

	/** First init ever called. */
	virtual void PreInit();

	void EngineInit(int argc, char* argv[]);

	/** Init (Inits SDL, Engine stuff). */
	virtual void Init();

	/** Third init function. */
	virtual void PostInit();

	/** Is inside of loop. Runs until Exit() is called. */
	void EngineTick();

	/** To be subproject overriden. Called each frame */
	virtual void Tick();

	void EnginePostSecondTick();

	/** To be subproject overriden. Called every second */
	virtual void PostSecondTick();

	/** MainLoop() runs untill this return false. */
	virtual bool CanContinueMainLoop() const;

	/** True if framerate limit is enabled. */
	virtual bool IsFrameRateLimited() const;

	/** Call to stop main loop. (Exit engine) */
	virtual void Stop();

	/** Called when main loops stop but before destructor. */
	virtual void PreExit();

	/** Clean up memory. (Remember to call parent! Otherwise you will leak memory.) */
	virtual void Clean();

	/** @Returns true if Init() has finished */
	bool IsEngineInitialized() const;

private:
	bool bContinueMainLoop;

protected:
	bool bFrameRateLimited;
	bool bIsEngineInitialized;

public:
	virtual void UpdateFrameTimeStart();
	virtual void UpdateFrameTimeEnd();

	uint32_t GetFrameTime() const;
	uint32_t GetFrameDelay() const;

	// Use to set engine frame rate - ticks per second
	virtual void SetFrameRate(uint32_t NewFrameRate);

	int GetFramesThisSecond() const;

protected:
	// Framerate per second / ticks per second
	uint32_t FPS;
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
	FEnginerRender* GetEngineRender() const;

	/** Use this if you changed to your own. Will return casted. */
	template<typename TRenderClass>
	inline FEnginerRender* GetEngineRenderCasted() const
	{
		static_cast<TRenderClass>(GetEngineRender());
	}

protected:
	FEnginerRender* EngineRender;

	virtual FEnginerRender* CreateEngineRenderer();






	static SDL_Event Event;
	//static AssetsManager* Assets;


};
