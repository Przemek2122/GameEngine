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
	friend FEngine;

public:
	FRenderThread(FThreadInputData* InThreadInputData, FThreadData* InThreadData);
	~FRenderThread() override;

	void StartThread() override;
	void StopThread() override;

	bool IsRenderingFrameFinished() const { return bIsRenderingFrameFinished; }

protected:
	void TickThread() override;

	void RenderNextFrame();

protected:
	/** Render commands collected during frame */
	CMap<ERenderOrder, FRenderDelegate*> RenderCommands;

	/** Render commands to actually render */
	CMap<ERenderOrder, FRenderDelegate*> RenderCommandsCopy;

	/** True if thread has finished work for this engine tick */
	std::atomic_bool bIsRenderingFrameFinished;

	/** Will be set from engine when tick is finished. */
	std::atomic_bool bIsRenderingNextFrameAllowed;

};
