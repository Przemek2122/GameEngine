//

#include "CoreEngine.h"
#include "EngineRender.h"

FEnginerRender::FEnginerRender()
	: bIsRenderTickFinished(true)
{
}

FEnginerRender::~FEnginerRender()
{
}

void FEnginerRender::StartRenderTick()
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

bool FEnginerRender::IsRenderTickFinished() const
{
	return bIsRenderTickFinished;
}

void FEnginerRender::RenderTick()
{
	for (FWindow* Window : ManagedWindows)
	{
		if (Window != nullptr)
		{

		}
		else
		{
			ENSURE("Empty pointer found!");
		}
	}

	EndRenderTick();
}

void FEnginerRender::EndRenderTick()
{
	bIsRenderTickFinished = true;
}

void FEnginerRender::DestroyWindow(FWindow* InWindow)
{
	ManagedWindows.Remove(InWindow);

	delete InWindow;
}

void FEnginerRender::AddWindow(FWindow* InWindow)
{
	ManagedWindows.Push(InWindow);
}

void FEnginerRender::RemoveWindow(FWindow* InWindow)
{
	ManagedWindows.Remove(InWindow);
}
