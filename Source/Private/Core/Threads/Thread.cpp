#include "CoreEngine.h"
#include "Threads/Thread.h"

#include "Threads/ThreadsManager.h"

FThreadInputData::FThreadInputData(FThreadsManager* InThreadsManager, const std::string& InThreadName)
	: Thread(nullptr)
	, ThreadsManager(InThreadsManager)
	, bThreadAlive(true)
{
}

const std::string& FThreadInputData::GetThreadName() const
{
	return ThreadName;
}

bool FThreadInputData::IsThreadAlive() const
{
	return bThreadAlive;
}

void FThread::TickThread()
{
	FThreadsManager* ThreadsManager = ThreadData->GetThreadsManager();
	while(ThreadData->IsThreadAlive() && ThreadsManager->HasAnyJobLeft())
	{
		FAsyncWorkStructure AsyncWorkStructure = ThreadsManager->GetFirstAvailableJob();

		// Run job to be done async
		AsyncWorkStructure.DelegateToRunAsync->Execute();

		if (AsyncWorkStructure.AsyncCallback)
		{
			// Enqueue sync callback on main thread
			ThreadsManager->MainThreadCallbacks.PushBackSafe(FMainThreadCallbackStructure(AsyncWorkStructure.AsyncCallback));
		}
	}

	SDL_Delay(1);
}

FThread::FThread(FThreadInputData* InThreadData)
	: ThreadData(InThreadData)
	, SDLThread(nullptr)
{
}

FThread::~FThread()
{
	if (SDLThread != nullptr)
	{
		SDL_DetachThread(SDLThread);
	}
}

void FThread::StartThread()
{
	SDL_CreateThread(FThread::ThreadFunction, ThreadData->GetThreadName().c_str(), ThreadData);
}

int FThread::ThreadFunction(void* InputData)
{
	FThreadInputData* ThreadData = static_cast<FThreadInputData*>(InputData);
	FThread* Thread = ThreadData->GetThread();

	while (ThreadData->IsThreadAlive())
	{
		Thread->TickThread();
	}

	return 0;
}
