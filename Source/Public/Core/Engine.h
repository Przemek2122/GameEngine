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

	virtual void Tick();

	/** MainLoop() runs untill this return false. */
	virtual bool CanContinueMainLoop() const;

	/** True if framerate limit is enabled. */
	virtual bool IsFrameRateLimited() const;

	/** Call to stop main loop. (Exit engine) */
	virtual void Stop();

	/** Called when main loops stop but before destructor. */
	virtual void PreExit();

	/** Clean up memory. */
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

	

protected:
	// Framerate per second / ticks per second
	uint32_t FPS;
	// Cached per frame delay for example 60 FPS will be 60 / 1000 = 16
	uint32_t FrameDelay;

	// Time ms of frame start
	uint32_t FrameStart;
	// Time ms of frame end
	uint32_t FrameTime;

	// Deltatime
	uint64_t CounterLastFrame;
	uint64_t CounterCurrentFrame = SDL_GetPerformanceCounter();

public:
	template<class TWindow>
	FWindow* CreateWindow(char* InTitle, int InPositionX, int InPositionY, int InWidth, int InHeight, Uint32 InFlags = 0)
	{
		TWindow* NewWindow = new TWindow(InTitle, InPositionX, InPositionY, InWidth, InHeight, InFlags);

		WindowsManaged.Push(NewWindow);
	}

	bool DestroyWindow(FWindow* Window)
	{
		WindowsManaged.Remove(Window);
	}

protected:
	/** Array of windows managed by this engine. */
	CArray<FWindow*> WindowsManaged;



	static SDL_Event Event;
	//static AssetsManager* Assets;


};
