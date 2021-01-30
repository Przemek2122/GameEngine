// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "EngineRender.h"

FEngineRender::FEngineRender()
	: bIsRenderTickFinished(true)
{
}

FEngineRender::~FEngineRender()
{
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
		ENSURE_VALID_MESSAGE(false, "Called too early");
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
			ENSURE_VALID_MESSAGE(false, "Empty pointer found!");
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
	ManagedWindows.Remove(InWindow);

	delete InWindow;
}

void FEngineRender::AddWindow(FWindow* InWindow)
{
	ManagedWindows.Push(InWindow);
}

void FEngineRender::RemoveWindow(FWindow* InWindow)
{
	ManagedWindows.Remove(InWindow);
}

FWindow* FEngineRender::GetFocusedWindow() const
{
	for (int i = 0; i < ManagedWindows.Size(); i++)
	{
		if (ManagedWindows[i]->IsWindowFocused())
		{
			return ManagedWindows[i];
		}
	}

	return nullptr;
}
