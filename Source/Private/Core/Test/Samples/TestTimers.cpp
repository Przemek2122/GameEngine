// Created by Przemys�aw Wiewi�ra 2024

#include "CoreEngine.h"
#include "Test/Samples/TestTimers.h"

#if ENGINE_TESTS_ALLOW_ANY
#include "Timer/Timer.h"
#include "Timer/TimerManager.h"

FTimersLongRunTest::FTimersLongRunTest()
	: CurrentNumberOfTimer2Runs(0)
	, MaxNumberOfTimer2Runs(3)
{
}

void FTimersLongRunTest::InitializeTest()
{
	StartTimer1();

	StartTimer2();
}

char* FTimersLongRunTest::GetTestName() const
{
	return TEXT_CHAR("Timers test");
}

void FTimersLongRunTest::StartTimer1()
{
	FDelegateSafe<void, FOptionalTimerParams*> TimerDelegate;
	TimerDelegate.BindLambda([&](FOptionalTimerParams*)
	{
		LOG_INFO("Timer (sync thread) finished.");
		LOG_INFO("Time elapsed since timer start: " << TemporaryTimer1->GetTimeElapsedSinceStart());

		CheckIfAllTimersFinishedAndFinishTest();
	});

	TemporaryTimer1 = FTimerManager::CreateTimerSync(TimerDelegate, 2.f);
}

void FTimersLongRunTest::StartTimer2()
{
	TemporaryTimer2 = FTimerManager::CreateTimerAsync([&](FOptionalTimerParams*)
	{
		LOG_INFO("Timer (sync thread) finished.");
		LOG_INFO("Time elapsed since timer start: " << TemporaryTimer2->GetTimeElapsedSinceStart());

		CurrentNumberOfTimer2Runs++;

		if (CurrentNumberOfTimer2Runs > MaxNumberOfTimer2Runs)
		{
			TemporaryTimer2->StartTimer(true);
		}

		CheckIfAllTimersFinishedAndFinishTest();
	}, 1.f);
}

void FTimersLongRunTest::CheckIfAllTimersFinishedAndFinishTest()
{
	if (!TemporaryTimer1->IsActive() && !TemporaryTimer2->IsActive())
	{
		EndTask();
	}
}
#endif