// Created by Przemys³aw Wiewióra 2024

#pragma once

#include "CoreMinimal.h"
#include "Threads/Thread.h"

typedef FDelegateSafe<void> FRenderDelegate;

enum class ERenderOrder : Uint8
{
	Pre,
	Default,
	Post
};

class FRenderThread : public FThread
{
public:
	FRenderThread(FThreadInputData* InThreadInputData, FThreadData* InThreadData);
	~FRenderThread();

	void StartThread() override;
	void StopThread() override;

	bool IsThreadFinished() const { return bIsThreadFinished; }

protected:
	void TickThread() override;

protected:
	/** Render commands to execute on render thread */
	CMap<ERenderOrder, FRenderDelegate*> RenderCommands;

	/** True if thread has finished work for this engine tick */
	std::atomic_bool bIsThreadFinished;

};
