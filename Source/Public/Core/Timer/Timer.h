// Created by Przemys³aw Wiewióra 2024

#pragma once

class FTimer;

/**
 * Optional params. Must not be created as null or timer will not start.
 * You can extend this struct to pass any needed parameters.
 */
struct FOptionalTimerParams
{
	FTimer* Timer;
};

/**
 * Timer class is used for managing raw sdl timer.
 * It has FOptionalTimerParams that will be passed to delegate on timer finish. if needed you can override it and pass custom
 */
class FTimer
{
public:
	/**
	 * Constructor using float. 1 MS equals 0.001.
	 * Note: Timer should not extend 49 days as single call.
	 */
	FTimer(FDelegateSafe<void, FOptionalTimerParams*>& InOnFinishDelegate, const float Time, std::shared_ptr<FOptionalTimerParams> InOptionalTimerParams = nullptr, bool bInRunAsyncOnFinish = true);

	/**
	 * Constructor using integer.
	 * Note: Timer should not extend 49 days as single call.
	 */
	FTimer(FDelegateSafe<void, FOptionalTimerParams*>& InOnFinishDelegate, const Uint32 Time, std::shared_ptr<FOptionalTimerParams> InOptionalTimerParams = nullptr, bool bInRunAsyncOnFinish = true);

	~FTimer();

	/** Called when timer finishes */
	static Uint32 OnTimerFinished(Uint32 InInterval, void* InOptionalTimerParams);

	/** Start timer */
	void StartTimer();

	/** Stop timer to save timer */
	void StopTimer();

	/** returns time left using conversion to float */
	float GetTimeLeft() const;

	/** @returns time left using variable - performance efficient */
	Uint32 GetTimeLeftRaw() const;

	SDL_TimerID GetTimerId() const;

protected:
	/** Function used by constructors to run function */
	void InitializeTimer();

	static Uint32 TimeFloatToMs(const float Time);
	static float TimeMsToFloat(const Uint32 Time);

private:
	/** if true OnFinishDelegate will be called async */
	bool bRunAsyncOnFinish;

	/** True if running, false if paused */
	bool bIsTimerActive;

	/** Delegate called when  */
	FDelegateSafe<void, FOptionalTimerParams*> OnFinishDelegate;

	/** Optional parameters passed in with delegates */
	std::shared_ptr<FOptionalTimerParams> OptionalTimerParams;

	/** Time left of time set on begging or pause */
	Uint32 TimeLeftRaw;

	/** Time since app start of when timer was started */
	Uint64 TimeStartOfTimer;

	SDL_TimerID TimerIDRaw;

};
