#include "CoreEngine.h"
#include "Threads/RenderThread.h"

FRenderThread::FRenderThread(FThreadInputData* InThreadInputData, FThreadData* InThreadData)
	: FThread(InThreadInputData, InThreadData)
{
}

FRenderThread::~FRenderThread()
{
	for (const std::pair<const ERenderOrder, FRenderDelegate*>& RenderCommand : RenderCommands)
	{
		delete RenderCommand.second;
	}

	RenderCommands.Clear();
}

void FRenderThread::StartThread()
{
	RenderCommands.Emplace(ERenderOrder::Pre, new FRenderDelegate());
	RenderCommands.Emplace(ERenderOrder::Default, new FRenderDelegate());
	RenderCommands.Emplace(ERenderOrder::Post, new FRenderDelegate());

	FThread::StartThread();
}

void FRenderThread::StopThread()
{
	FThread::StopThread();
}

void FRenderThread::TickThread()
{
	bIsRenderingFrameFinished = false;

	// Copy data for render
	RenderCommandsCopy = RenderCommands;

	// Clear copied data
	for (const std::pair<const ERenderOrder, FRenderDelegate*>& RenderCommand : RenderCommands)
	{
		RenderCommand.second->UnBindAll();
	}

	// Execute
	for (const std::pair<const ERenderOrder, FRenderDelegate*>& RenderCommand : RenderCommandsCopy)
	{
		RenderCommand.second->Execute();
	}

	bIsRenderingFrameFinished = true;

	while (!bIsRenderingNextFrameAllowed)
	{
		THREAD_WAIT_SHORT_TIME;
	}

	bIsRenderingNextFrameAllowed = false;
}

void FRenderThread::RenderNextFrame()
{
	bIsRenderingNextFrameAllowed = true;
}
