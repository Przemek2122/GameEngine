#include "CoreEngine.h"
#include "Threads/RenderThread.h"

FRenderCommandsWithScopeLock::FRenderCommandsWithScopeLock(FRenderThread* InRenderThread)
	: RenderThread(InRenderThread)
{
	THREAD_WAIT_FOR_MUTEX_LOCK(RenderThread->RenderCommandsMutex);
}

FRenderCommandsWithScopeLock::~FRenderCommandsWithScopeLock()
{
#if _DEBUG
	// Lock released before it should be released
	ENSURE_VALID(RenderThread->RenderCommandsMutex.IsLocked());
#endif

	RenderThread->RenderCommandsMutex.Unlock();
}

FRenderDelegate* FRenderCommandsWithScopeLock::GetRenderDelegate(const ERenderOrder RenderOrder) const
{
	return RenderThread->RenderCommands[RenderOrder];
}

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
	InitializeMapWithDelegates();

	FThread::StartThread();
}

void FRenderThread::StopThread()
{
	FThread::StopThread();
}

FRenderCommandsWithScopeLock FRenderThread::GetRenderCommands()
{
	return FRenderCommandsWithScopeLock(this);
}

void FRenderThread::TickThread()
{
	bIsRenderingFrameFinished = false;

	// Lock RenderCommandsMutex for copy
	THREAD_WAIT_FOR_MUTEX_LOCK(RenderCommandsMutex);

	// Copy data for render
	RenderCommandsCopy = std::move(RenderCommands);

	InitializeMapWithDelegates();

	RenderCommandsMutex.Unlock();

	THREAD_WAIT_MS(5);

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

void FRenderThread::AllowRenderNextFrame()
{
	bIsRenderingNextFrameAllowed = true;
}

void FRenderThread::InitializeMapWithDelegates()
{
	RenderCommands.Emplace(ERenderOrder::Pre, new FRenderDelegate());
	RenderCommands.Emplace(ERenderOrder::Default, new FRenderDelegate());
	RenderCommands.Emplace(ERenderOrder::Post, new FRenderDelegate());
}
