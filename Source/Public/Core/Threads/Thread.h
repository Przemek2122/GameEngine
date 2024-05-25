// Created by Przemys³aw Wiewióra 2024

#pragma once

#include "CoreMinimal.h"

class FThreadData;
class FThread;
class FThreadsManager;

struct FThreadInputData
{
	friend FThreadData;
	friend FThreadsManager;

public:
	FThreadInputData(FThreadsManager* InThreadsManager, const std::string& InThreadName);

	FThread* GetThread() const { return Thread; }
	FThreadsManager* GetThreadsManager() const { return ThreadsManager; }

	const std::string& GetThreadName() const;

	bool IsThreadAlive() const;

private:
	FThread* Thread;
	FThreadsManager* ThreadsManager;

	/** Thread name visible in debugger etc... */
	std::string ThreadName;

	/** This setting is used to stop thread. */
	bool bThreadAlive;

};

class FThread
{
	friend FThreadsManager;
	friend FThreadData;

protected:
	FThread(FThreadInputData* InThreadData);
	virtual ~FThread();

	void StartThread();

	/** Thread function used by SDL */
	static int ThreadFunction(void* InputData);

	virtual void TickThread();

	FThreadInputData* GetThreadData() const { return ThreadData; }

private:
	FThreadInputData* ThreadData;

	SDL_Thread* SDLThread;

};
