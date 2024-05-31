#include "CoreEngine.h"
#include "Threads/ThreadsManager.h"

#include "Mutex/MutexScopeLock.h"

FThreadsManager::FThreadsManager()
	: StartingNumberOfThreads(4)
	, DefaultThreadName("DefaultThread_")
{
}

FThreadsManager::~FThreadsManager()
{
	// Stop created threads
	for (int i = 0; i < GetNumberOfWorkerThreads(); i++)
	{
		StopThread();
	}

	int TimeToStopThreads = 0;

	LOG_INFO("Number of threads to stop: " << WorkerThreadsArray.Size());

	// Wait for all threads to finish
	while (WorkerThreadsArray.Size())
	{
		SDL_Delay(1);

		TimeToStopThreads++;
	}

	LOG_INFO("Stopping threads took: " << TimeToStopThreads << "ms");
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
	while (AsyncJobQueueMutex.IsLocked())
	{
		SDL_Delay(1);
	}

	FMutexScopeLock MutexScopeLock(AsyncJobQueueMutex);

	AsyncJobQueue.PushBack(AsyncRunWithCallback);
}

FThreadWorkerData* FThreadsManager::CreateThreadWorker(const std::string& NewThreadName)
{
	return CreateThread<FThreadWorker, FThreadWorkerData>(NewThreadName);
}

void FThreadsManager::StartNewThread()
{
	if (!AvailableThreadsNumbers.IsEmpty())
	{
		FMutexScopeLock MutexScopeLock(WorkerThreadsArrayMutex);

		const int NewThreadIndex = AvailableThreadsNumbers[0];
		AvailableThreadsNumbers.RemoveAt(0);

		const std::string NewThreadName = DefaultThreadName + std::to_string(NewThreadIndex + 1);

		FThreadWorkerData* ThreadData = CreateThreadWorker(NewThreadName);
		ThreadData->ThreadNumber = NewThreadIndex;

		WorkerThreadsArray.Push(ThreadData);
	}
}

void FThreadsManager::StopThread()
{
	int ThreadIndex = WorkerThreadsArray.Size() - 1;

	FThreadWorkerData* LastAliveThread = WorkerThreadsArray[ThreadIndex];

	// Find last still alive thread
	while (ThreadIndex >= 0 && !LastAliveThread->ThreadInputData->IsThreadAlive())
	{
		ThreadIndex--;

		LastAliveThread = WorkerThreadsArray[ThreadIndex];
	}

	AvailableThreadsNumbers.Push(LastAliveThread->ThreadNumber);

	// Stop thread
	if (LastAliveThread->ThreadInputData->IsThreadAlive())
	{
		LastAliveThread->Thread->StopThread();
	}
	else
	{
		LOG_WARN("Stopping thread failed. Already stopped.");
	}
}

int FThreadsManager::GetNumberOfWorkerThreads() const
{
	return WorkerThreadsArray.Size();
}

int FThreadsManager::GetNumberOfCores()
{
	return SDL_GetCPUCount();
}

FAsyncWorkStructure FThreadsManager::GetFirstAvailableJob()
{
	// @TODO Remove mutex and find and smart way of distributing tasks
	// In worse case update to SDL3 and use SDL_DelayNS

	while (AsyncJobQueueMutex.IsLocked())
	{
		SDL_Delay(1);
	}

	FMutexScopeLock MutexScopeLock(AsyncJobQueueMutex);

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

		return std::move(AsyncWorkStructure);
	}
}

bool FThreadsManager::HasAnyJobLeft() const
{
	return (AsyncJobQueue.Size() > 0);
}

void FThreadsManager::InternalRemoveWorkerThread(const FThread* InThread)
{
	FMutexScopeLock MutexScopeLock(WorkerThreadsArrayMutex);

	// Remove thread data from array
	WorkerThreadsArray.Remove(InThread->GetThreadData());
}
