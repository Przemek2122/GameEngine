// Created by Przemys³aw Wiewióra 2020

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
	void Tick();
	/** Called from engine when new render Tick should be started */
	void StartRenderTick();
	/** @returns true when rendering for this frame is ended. */
	_NODISCARD bool IsRenderTickFinished() const;

protected:
	bool bIsRenderTickFinished;

protected:
	void AddWindow(FWindow* InWindow);
	void RemoveWindow(FWindow* InWindow);

	/** Render thread tick. */
	void RenderTick();
	/** Called when RenderTick finishes */
	void EndRenderTick();

public:
	/** Create window from template class */
	template<class TWindow, typename... TInParams>
	FWindow* CreateWindow(TInParams... InParams)
	{
		TWindow* NewWindow = new TWindow(InParams...);

		NewWindow->Init();

		AddWindow(NewWindow);

		return NewWindow;
	}
	
	/** Destroy and remove window by class. */
	void DestroyWindow(FWindow* InWindow);

	/** @returns window pointer or nullptr if there is no focused window. */
	_NODISCARD FWindow* GetFocusedWindow() const;

	_NODISCARD FWindow* GetWindowById(Uint32 WindowId);

	void OnWindowExposed(Uint32 WindowId);
	void OnWindowHidden(Uint32 WindowId);

	void OnWindowMoved(Uint32 WindowId, Sint32 X, Sint32 Y);
	void OnWindowResized(Uint32 WindowId, Sint32 X, Sint32 Y);
	void OnWindowSizeChanged(Uint32 WindowId, Sint32 X, Sint32 Y);
	void OnWindowMinimized(Uint32 WindowId);
	void OnWindowMaximized(Uint32 WindowId);

protected:
	/** Array of windows managed by this engine. */
	CArray<FWindow*> ManagedWindows;
	CMap<Uint32, FWindow*> WindowToIdMap;

};

#define FOR_EACH()
