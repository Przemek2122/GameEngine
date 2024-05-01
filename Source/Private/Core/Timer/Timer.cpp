// Created by Przemys³aw Wiewióra 2024

#include "CoreEngine.h"
#include "Timer/Timer.h"

static constexpr int TimeConversionMultiplier = 1000;

FTimer::FTimer(FDelegateSafe<void, FOptionalTimerParams*>& InOnFinishDelegate, const float Time, std::shared_ptr<FOptionalTimerParams> InOptionalTimerParams, const bool bInRunAsyncOnFinish)
	: bRunAsyncOnFinish(bInRunAsyncOnFinish)
	, bIsTimerActive(false)
	, OnFinishDelegate(std::move(InOnFinishDelegate))
	, OptionalTimerParams(std::move(InOptionalTimerParams))
	, TimeLeftRaw(TimeFloatToMs(Time))
{
	InitializeTimer();
}

FTimer::FTimer(FDelegateSafe<void, FOptionalTimerParams*>& InOnFinishDelegate, const Uint32 Time, std::shared_ptr<FOptionalTimerParams> InOptionalTimerParams, bool bInRunAsyncOnFinish)
	: bRunAsyncOnFinish(bInRunAsyncOnFinish)
	, bIsTimerActive(false)
	, OnFinishDelegate(std::move(InOnFinishDelegate))
	, OptionalTimerParams(std::move(InOptionalTimerParams))
	, TimeLeftRaw(Time)
{
	InitializeTimer();
}

FTimer::~FTimer()
{
	StopTimer();
}

Uint32 FTimer::OnTimerFinished(Uint32 InInterval, void* InOptionalTimerParams)
{
	FOptionalTimerParams* OptionalTimerParams = static_cast<FOptionalTimerParams*>(InOptionalTimerParams);

	if (OptionalTimerParams->Timer->bRunAsyncOnFinish)
	{
		OptionalTimerParams->Timer->OnFinishDelegate.Execute(OptionalTimerParams);
	}
	else
	{
		// @TODO May be critical if two timers happen in same time
		GEngine->AddLambdaToCallOnStartOfNextTick([&]()
		{
			OptionalTimerParams->Timer->OnFinishDelegate.Execute(OptionalTimerParams);
		});
	}

	return 0;
}

void FTimer::StartTimer()
{
	if (!bIsTimerActive)
	{
		bIsTimerActive = true;

		TimeStartOfTimer = SDL_GetTicks64();

		TimerIDRaw = SDL_AddTimer(TimeLeftRaw, OnTimerFinished, OptionalTimerParams.get());
	}
}

void FTimer::StopTimer()
{
	if (!bIsTimerActive)
	{
		bIsTimerActive = true;

		SDL_RemoveTimer(TimerIDRaw);

		TimeLeftRaw = static_cast<Uint32>(SDL_GetTicks64() - TimeStartOfTimer);
	}
}

bool FTimer::IsActive() const
{
	return bIsTimerActive;
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

void FTimer::InitializeTimer()
{
	if (OptionalTimerParams != nullptr)
	{
		OptionalTimerParams->Timer = this;

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
