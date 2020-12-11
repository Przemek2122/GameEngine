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

	/** Init (Inits SDL, Engine stuff). */
	void Init(int argc, char* argv[]);

	virtual void GameInit();

	/** Third init function. */
	virtual void PostInit();

	/** Is inside of loop. Runs until Exit() is called. */
	virtual void MainLoop();

	/** MainLoop() runs untill this return false. */
	bool CanContinueMainLoop() const;

	/** True if framerate limit is enabled. */
	bool IsFrameRateLimit() const;

	/** Call to stop main loop. (Exit engine) */
	virtual void Stop();

	/** Called when main loops stop but before destructor. */
	virtual void PreExit();

	/** Clean up memory. */
	virtual void Clean();

	/** @Returns true if Init() has finished */
	bool IsEngineInitialized() const;

protected:
	bool bFrameRateLimit;
	bool bIsEngineInitialized;

	static SDL_Event Event;
	//static AssetsManager* Assets;

private:
	bool bContinueMainLoop;

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

};
