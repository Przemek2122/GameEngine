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
	: StartingNumberOfThreads(2)
	, DefaultThreadName("DefaultThread_")
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
	// Calculate number of cores
	int NumberOfCores = SDL_GetCPUCount();

	// Ensure we always have at least one thread.
	if (NumberOfCores <= 0)
	{
		NumberOfCores = 1;
	}

	// Create available slots for threads
	for (int ThreadIndex = 0; ThreadIndex < NumberOfCores; ThreadIndex++)
	{
		AvailableThreadsNumbers.Push(ThreadIndex);
	}

	// Create default number of threads
	for (int i = 0; i < StartingNumberOfThreads; i++)
	{
		StartNewThread();
	}
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

		const std::string NewThreadName = DefaultThreadName + std::to_string(NewThreadIndex + 1);

		FThreadData* ThreadData = CreateThread(NewThreadName);
		ThreadData->ThreadNumber = NewThreadIndex;

		AllThreadArray.Push(ThreadData);
	}
}

void FThreadsManager::StopThread()
{
	const int ThreadIndex = AllThreadArray.Size() - 1;

	FThreadData* LastThread = AllThreadArray[ThreadIndex];
	LastThread->ThreadInputData->bThreadAlive = false;

	AvailableThreadsNumbers.Push(LastThread->ThreadNumber);

	delete LastThread;

	AllThreadArray.RemoveAt(ThreadIndex);
}

int FThreadsManager::GetNumberOfCores()
{
	return SDL_GetCPUCount();
}

FAsyncWorkStructure FThreadsManager::GetFirstAvailableJob()
{
	// @TODO Remove mutex and find and smart way of distributing tasks

	while (!AsyncJobQueueMutex.try_lock())
	{
		SDL_Delay(1);
	}

	if (AsyncJobQueue.Size() == 0)
	{
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
