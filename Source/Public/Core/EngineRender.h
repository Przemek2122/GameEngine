//

#pragma once

#include "CoreMinimal.h"

/** Call for managing rendering (windows). */
class FEngineRender
{
	friend FEngine;

protected:
	FEngineRender();
	~FEngineRender();

public:
	/** Called from engine when new render Tick should be started */
	void StartRenderTick();
	/** @Returns true when rendering for this frame is ended. */
	bool IsRenderTickFinished() const;

protected:
	bool bIsRenderTickFinished;

protected:
	/** Render thread tick. */
	void RenderTick();
	/** Called when RenderTick finishes */
	void EndRenderTick();

public:
	/** Create window from template class */
	template<class TWindow>
	FWindow* CreateWindow(char* InTitle, int InPositionX, int InPositionY, int InWidth, int InHeight, Uint32 InFlags = 0)
	{
		TWindow* NewWindow = new TWindow(InTitle, InPositionX, InPositionY, InWidth, InHeight, InFlags);

		ManagedWindows.Push(NewWindow);
	};
	/** Destroy and remove window by class. */
	void DestroyWindow(FWindow* InWindow);

	/** Add window created outside to this class manager. */
	void AddWindow(FWindow* InWindow);
	/** Remove window (will not be destroyed in this function). */
	void RemoveWindow(FWindow* InWindow);

	/** @returns window pointer or nullptr if there is no focused window. */
	FWindow* GetFocusedWindow() const;

protected:
	/** Array of windows managed by this engine. */
	CArray<FWindow*> ManagedWindows;

};

#define FOR_EACH()
