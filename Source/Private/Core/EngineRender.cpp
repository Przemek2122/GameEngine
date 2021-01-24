// Created by Przemys�aw Wiewi�ra 2020

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

	else
	{
		ENSURE("Called too early");
	}
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
		else
		{
			ENSURE("Empty pointer found!");
		}
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
