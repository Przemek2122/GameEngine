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
	COUNTER_START(RenderThreadTickCounterStart);

	for (const std::pair<const ERenderOrder, FRenderDelegate*>& RenderCommand : RenderCommands)
	{
		RenderCommand.second->Execute();
	}

	THREAD_WAIT_NS(100000);

	COUNTER_END(RenderThreadTickCounterStart, RenderThreadTickCounterEnd);

	LOG_INFO("Render thread took: " << COUNTER_GET(RenderThreadTickCounterEnd));

	FThread::TickThread();
}
