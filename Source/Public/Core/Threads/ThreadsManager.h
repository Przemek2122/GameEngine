// Created by Przemys³aw Wiewióra 2024

#pragma once

#include "CoreMinimal.h"
#include "Thread.h"

class FThreadData
{
	friend FThreadsManager;

public:
	FThreadData(FThreadsManager* InThreadsManager, const std::string& InNewThreadName);
	~FThreadData();

protected:
	FThreadInputData* ThreadInputData;
	FThread* Thread;

	int ThreadNumber;

};

struct FAsyncWorkStructure
{
	std::shared_ptr<FDelegateSafe<>> DelegateToRunAsync;
	std::shared_ptr<FDelegateSafe<>> AsyncCallback;
};

struct FMainThreadCallbackStructure
{
	FMainThreadCallbackStructure(const std::shared_ptr<FDelegateSafe<>>& InAsyncCallback)
		: AsyncCallback(InAsyncCallback)
	{
	}

	std::shared_ptr<FDelegateSafe<>> AsyncCallback;
};

/**
 * Class for managing threads using SDL2.
 */
class FThreadsManager
{
	friend FThread;

public:
	FThreadsManager();
	~FThreadsManager();

	/** Should be called when class is set up to setup available threads */
	void Initialize();

	/** Runs callbacks on main thread */
	void TickThreadCallbacks();

	/** Add delegate which will be run on first available async thread */
	void AddAsyncDelegate(FDelegateSafe<>& DelegateToRunAsync);

	/** Add delegate which will be run on first available async thread */
	void AddAsyncDelegate(FDelegateSafe<>& DelegateToRunAsync, FDelegateSafe<>& AsyncCallback);

	/** Add delegate which will be run on first available async thread */
	void AddAsyncWork(const FAsyncWorkStructure& AsyncRunWithCallback);

protected:
	/** Creates thread for use */
	FThreadData* CreateThread(const std::string& NewThreadName);

	/** Get an array with created threads */
	const CArray<FThreadData*>& GetThreadArray() const;

	/** Starts a new thread if there is free number in pool available, see param AvailableThreadsNumbers */
	void StartNewThread();

	/** Stops one thread */
	void StopThread();

	/** @returuns number of system available cores */
	static int GetNumberOfCores();

	/** Used by threads to actually do the job */
	FAsyncWorkStructure GetFirstAvailableJob();

	bool HasAnyJobLeft() const;

	/** Queue of async jobs to be done */
	CDeque<FAsyncWorkStructure> AsyncJobQueue;

	/** Mutex for param AsyncJobQueue */
	std::mutex AsyncJobQueueMutex;

	/** Callbacks from finishes async jobs */
	CQueueSafe<FMainThreadCallbackStructure> MainThreadCallbacks;

	int StartingNumberOfThreads;

private:
	/** Array with created threads */
	CArray<FThreadData*> AllThreadArray;

	/** Number with thread Id for naming */
	CArray<int> AvailableThreadsNumbers;

	/** Default name of thread, at end number will be added */
	std::string DefaultThreadName;

};
