// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "EngineRender.h"

FEngineRender::FEngineRender()
	: bIsRenderTickFinished(true)
{
}

FEngineRender::~FEngineRender()
{
	for (auto i = ManagedWindows.Size() - 1; ManagedWindows.Size() > 0; i--)
	{
		DestroyWindow(ManagedWindows[i]);
	}
}

void FEngineRender::Tick()
{
	StartRenderTick();
	
	for (FWindow* Window : ManagedWindows.Vector)
	{
		Window->ReceiveTick();
	}
}

void FEngineRender::StartRenderTick()
{
	if (bIsRenderTickFinished)
	{
		bIsRenderTickFinished = false;

		// @TODO Move to thread.
		RenderTick();
	}
#if _DEBUG
	else
	{
		ENSURE_VALID(false);
	}
#endif
}

bool FEngineRender::IsRenderTickFinished() const
{
	return bIsRenderTickFinished;
}

void FEngineRender::RenderTick()
{
	for (FWindow* Window : ManagedWindows.Vector)
	{
		if (Window != nullptr)
		{
			Window->Render();
		}
#ifdef _DEBUG
		else
		{
			ENSURE_VALID(false);
		}
#endif
	}

	EndRenderTick();
}

void FEngineRender::EndRenderTick()
{
	bIsRenderTickFinished = true;
}

void FEngineRender::DestroyWindow(FWindow* InWindow)
{
	RemoveWindow(InWindow);

	delete InWindow;
}

void FEngineRender::AddWindow(FWindow* InWindow)
{
	ManagedWindows.Push(InWindow);

	WindowToIdMap.Emplace(SDL_GetWindowID(InWindow->GetSdlWindow()), InWindow);
}

void FEngineRender::RemoveWindow(FWindow* InWindow)
{
	ManagedWindows.Remove(InWindow);

	WindowToIdMap.Remove(InWindow->WindowId);
}

FWindow* FEngineRender::GetFocusedWindow() const
{
	for (auto i = 0; i < ManagedWindows.Size(); i++)
	{
		if (ManagedWindows[i]->IsWindowFocused())
		{
			return ManagedWindows[i];
		}
	}

	return nullptr;
}

FWindow* FEngineRender::GetWindowById(Uint32 WindowId)
{
	if (WindowToIdMap.HasKey(WindowId))
	{
		return WindowToIdMap[WindowId];
	}

	return nullptr;
}

void FEngineRender::OnWindowExposed(const Uint32 WindowId)
{
	FWindow* Window = GetWindowById(WindowId);
	if (Window != nullptr)
	{
		// @TODO OnWindowExposed...
	}
}

void FEngineRender::OnWindowHidden(const Uint32 WindowId)
{
	FWindow* Window = GetWindowById(WindowId);
	if (Window != nullptr)
	{
		// @TODO OnWindowHidden...
	}
}

void FEngineRender::OnWindowMoved(const Uint32 WindowId, const Sint32 X, const Sint32 Y)
{
	FWindow* Window = GetWindowById(WindowId);
	if (Window != nullptr)
	{
		Window->SetWindowLocation(X, Y, false);
	}
}

void FEngineRender::OnWindowResized(const Uint32 WindowId, const Sint32 X, const Sint32 Y)
{
	FWindow* Window = GetWindowById(WindowId);
	if (Window != nullptr)
	{
		Window->Renderer->SetWindowSize(X, Y, false);
	}
}

void FEngineRender::OnWindowSizeChanged(const Uint32 WindowId, const Sint32 X, const Sint32 Y)
{
	FWindow* Window = GetWindowById(WindowId);
	if (Window != nullptr)
	{
		Window->Renderer->SetWindowSize(X, Y, false);
	}
}

void FEngineRender::OnWindowMinimized(const Uint32 WindowId)
{
	FWindow* Window = GetWindowById(WindowId);
	if (Window != nullptr)
	{
		// @TODO OnWindowMinimized...
	}
}

void FEngineRender::OnWindowMaximized(const Uint32 WindowId)
{
	FWindow* Window = GetWindowById(WindowId);
	if (Window != nullptr)
	{
		// @TODO OnWindowMaximized...
	}
}
