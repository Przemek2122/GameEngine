// Created by Przemys³aw Wiewióra 2024

#include "CoreEngine.h"
#include "Timer/Timer.h"

static constexpr int TimeConversionMultiplier = 1000;

FTimerCollector::FTimerCollector()
	: bAreTimersPaused(false)
{
}

FTimerCollector* FTimerCollector::Get()
{
	static FTimerCollector* TimerCollector = new FTimerCollector();

	return TimerCollector;
}

void FTimerCollector::RegisterTimer(FTimer* Timer)
{
	Timers.Push(Timer);
}

void FTimerCollector::UnRegisterTimer(FTimer* Timer)
{
	Timers.Remove(Timer);

	PausedTimers.Remove(Timer);
}

void FTimerCollector::PauseAllTimers()
{
	if (!bAreTimersPaused)
	{
		bAreTimersPaused = true;

		for (FTimer* CurrentTimer : Timers)
		{
			if (CurrentTimer != nullptr && CurrentTimer->IsActive() && CurrentTimer->IsPausableByTimerCollector())
			{
				PausedTimers.Push(CurrentTimer);

				CurrentTimer->PauseTimer();
			}
		}
	}
}

void FTimerCollector::ResumeAllTimers()
{
	if (bAreTimersPaused)
	{
		bAreTimersPaused = false;

		for (FTimer* PausedTimer : PausedTimers)
		{
			PausedTimer->StartTimer();
		}

		PausedTimers.Clear();
	}
}

FTimer::FTimer(FDelegateSafe<void, FOptionalTimerParams*>& InOnFinishDelegate, const float Time, std::shared_ptr<FOptionalTimerParams> InOptionalTimerParams, const bool bInRunAsyncOnFinish)
	: bRunAsyncOnFinish(bInRunAsyncOnFinish)
	, bIsTimerActive(false)
	, OnFinishDelegate(std::move(InOnFinishDelegate))
	, OptionalTimerParams(std::move(InOptionalTimerParams))
	, TimeLeftRaw(TimeFloatToMs(Time))
	, InitialTimerTime(TimeLeftRaw)
{
	FTimerCollector::Get()->RegisterTimer(this);

	InitializeTimer();
}

FTimer::FTimer(FDelegateSafe<void, FOptionalTimerParams*>& InOnFinishDelegate, const Uint32 Time, std::shared_ptr<FOptionalTimerParams> InOptionalTimerParams, bool bInRunAsyncOnFinish)
	: bRunAsyncOnFinish(bInRunAsyncOnFinish)
	, bIsTimerActive(false)
	, OnFinishDelegate(std::move(InOnFinishDelegate))
	, OptionalTimerParams(std::move(InOptionalTimerParams))
	, TimeLeftRaw(Time)
	, InitialTimerTime(TimeLeftRaw)
{
	FTimerCollector::Get()->RegisterTimer(this);

	InitializeTimer();
}

FTimer::~FTimer()
{
	FTimerCollector::Get()->UnRegisterTimer(this);

	PauseTimer();
}

Uint32 FTimer::OnTimerFinished(Uint32 InInterval, void* InOptionalTimerParams)
{
	FOptionalTimerParams* OptionalTimerParams = static_cast<FOptionalTimerParams*>(InOptionalTimerParams);

	OptionalTimerParams->Timer->bIsTimerActive = false;

	if (OptionalTimerParams->Timer->bRunAsyncOnFinish)
	{
		OptionalTimerParams->Timer->OnFinishDelegate.Execute(OptionalTimerParams);
	}
	else
	{
		// @TODO May be critical if two timers happen in same time
		GEngine->AddLambdaToCallOnStartOfNextTick([OptionalTimerParams]()
		{
			OptionalTimerParams->Timer->OnSynchronousTimerFinished();
		});
	}

	return 0;
}

void FTimer::OnSynchronousTimerFinished()
{
	OnFinishDelegate.Execute(OptionalTimerParams.get());
}

void FTimer::StartTimer(const bool bRestartTimer)
{
	if (!bIsTimerActive)
	{
		bIsTimerActive = true;

		if (bRestartTimer)
		{
			TimeLeftRaw = InitialTimerTime;
		}

		TimeStartOfTimer = SDL_GetTicks64();

		TimerIDRaw = SDL_AddTimer(TimeLeftRaw, OnTimerFinished, OptionalTimerParams.get());
	}
}

void FTimer::PauseTimer()
{
	if (bIsTimerActive)
	{
		bIsTimerActive = false;

		const bool bWasRemoved = SDL_RemoveTimer(TimerIDRaw);

		if (bWasRemoved)
		{
			TimeLeftRaw = static_cast<Uint32>(SDL_GetTicks64() - TimeStartOfTimer);
		}
		else
		{
			LOG_ERROR("Unable to remove timer.");
		}
	}
}

bool FTimer::IsActive() const
{
	return bIsTimerActive;
}

bool FTimer::IsPausableByTimerCollector()
{
	return true;
}

float FTimer::GetTimeLeft() const
{
	return TimeMsToFloat(TimeLeftRaw);
}

Uint32 FTimer::GetTimeLeftRaw() const
{
	return TimeLeftRaw;
}

Uint32 FTimer::GetTimeElapsedSinceStart() const
{
	return (SDL_GetTicks64() - TimeStartOfTimer);
}

SDL_TimerID FTimer::GetTimerId() const
{
	return TimerIDRaw;
}

FOptionalTimerParams* FTimer::GetOptionalTimerParams() const
{
	return OptionalTimerParams.get();
}

void FTimer::InitializeTimer()
{
	if (OptionalTimerParams != nullptr)
	{
		OptionalTimerParams->Timer = this;

		TimeStartOfTimer = SDL_GetTicks64();

		StartTimer();
	}
	else
	{
		LOG_ERROR("FOptionalTimerParams was passwed as nullptr. Timer will be inactive!");
	}
}

Uint32 FTimer::TimeFloatToMs(const float Time)
{
	return static_cast<Uint32>(Time * static_cast<float>(TimeConversionMultiplier));
}

float FTimer::TimeMsToFloat(const Uint32 Time)
{
	return static_cast<float>(Time) / static_cast<float>(TimeConversionMultiplier);
}
