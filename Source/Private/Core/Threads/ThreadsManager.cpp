#include "CoreEngine.h"
#include "Threads/ThreadsManager.h"

FThreadData::FThreadData(FThreadsManager* InThreadsManager, const std::string& InNewThreadName)
	: ThreadInputData(new FThreadInputData(InThreadsManager, InNewThreadName))
	, Thread(nullptr)
{
	// Create thread
	Thread = new FThread(ThreadInputData);

	// Set thread references
	ThreadInputData->Thread = Thread;
}

FThreadData::~FThreadData()
{
	delete Thread;
	delete ThreadInputData;
}

FThreadsManager::FThreadsManager()
	: DefaultThreadName("DefaultThread_")
{
}

FThreadsManager::~FThreadsManager()
{
	for (FThreadData* ThreadData : AllThreadArray)
	{
		delete ThreadData;
	}
}

void FThreadsManager::Initialize()
{
	// Calculate number of cores - Remove one because of main thread
	int NumberOfCores = SDL_GetCPUCount() - 1;

	// Ensure we always have at least one thread.
	if (NumberOfCores <= 0)
	{
		NumberOfCores = 1;
	}

	for (int ThreadIndex = 0; ThreadIndex < NumberOfCores; ThreadIndex++)
	{
		AvailableThreadsNumbers.Push(ThreadIndex);
	}

	StartNewThread();
}

void FThreadsManager::TickThreadCallbacks()
{
	while(!MainThreadCallbacks.IsEmpty())
	{
		FMainThreadCallbackStructure CurrentFirstElement = std::move(MainThreadCallbacks.PeekFirst());

		MainThreadCallbacks.DequeFrontSafe();

		CurrentFirstElement.AsyncCallback->Execute();
	}
}

void FThreadsManager::AddAsyncDelegate(FDelegateSafe<void>& DelegateToRunAsync)
{
	FAsyncWorkStructure AsyncWorkStructure;
	AsyncWorkStructure.DelegateToRunAsync = std::make_shared<FDelegateSafe<void>>(std::move(DelegateToRunAsync));

	AddAsyncWork(AsyncWorkStructure);
}

void FThreadsManager::AddAsyncDelegate(FDelegateSafe<void>& DelegateToRunAsync, FDelegateSafe<void>& AsyncCallback)
{
	FAsyncWorkStructure AsyncWorkStructure;
	AsyncWorkStructure.DelegateToRunAsync = std::make_shared<FDelegateSafe<void>>(std::move(DelegateToRunAsync));
	AsyncWorkStructure.AsyncCallback = std::make_shared<FDelegateSafe<void>>(std::move(AsyncCallback));

	AddAsyncWork(AsyncWorkStructure);
}

void FThreadsManager::AddAsyncWork(const FAsyncWorkStructure& AsyncRunWithCallback)
{
	while (!AsyncJobQueueMutex.try_lock())
	{
		SDL_Delay(1);
	}

	AsyncJobQueue.PushBack(AsyncRunWithCallback);

	AsyncJobQueueMutex.unlock();
}

FThreadData* FThreadsManager::CreateThread(const std::string& NewThreadName)
{
	// Create thread
	FThreadData* ThreadData = new FThreadData(this, NewThreadName);

	// Start thread
	ThreadData->Thread->StartThread();

	return ThreadData;
}

const CArray<FThreadData*>& FThreadsManager::GetThreadArray() const
{
	return AllThreadArray;
}

void FThreadsManager::StartNewThread()
{
	if (!AvailableThreadsNumbers.IsEmpty())
	{
		const int NewThreadIndex = AvailableThreadsNumbers[0];
		AvailableThreadsNumbers.RemoveAt(0);

		// Thread name visible for example in debugger
		const std::string NewThreadName = DefaultThreadName + std::to_string(NewThreadIndex + 1);

		AllThreadArray.Push(CreateThread(NewThreadName));
	}
}

void FThreadsManager::StopThread()
{
	const int ThreadIndex = AllThreadArray.Size() - 1;

	FThreadData* LastThread = AllThreadArray[ThreadIndex];
	LastThread->ThreadInputData->bThreadAlive = false;

	AllThreadArray.RemoveAt(ThreadIndex);
}

int FThreadsManager::GetNumberOfCores()
{
	return SDL_GetCPUCount();
}

FAsyncWorkStructure FThreadsManager::GetFirstAvailableJob()
{
	while (!AsyncJobQueueMutex.try_lock())
	{
		SDL_Delay(1);
	}

	if (AsyncJobQueue.Size() == 0)
	{
		LOG_ERROR("AsyncJobQueue is empty. We should never try to get new async job when there is no any");

		FAsyncWorkStructure AsyncWorkStructure;
		AsyncWorkStructure.DelegateToRunAsync = std::make_shared<FDelegateSafe<>>();
		AsyncWorkStructure.AsyncCallback = std::make_shared<FDelegateSafe<>>();

		return AsyncWorkStructure;
	}
	else
	{
		// Get first element
		FAsyncWorkStructure AsyncWorkStructure = AsyncJobQueue.PeekFirst();

		// Remove first element from list
		AsyncJobQueue.DequeFront();

		AsyncJobQueueMutex.unlock();

		return std::move(AsyncWorkStructure);
	}
}

bool FThreadsManager::HasAnyJobLeft() const
{
	return (AsyncJobQueue.Size() > 0);
}
