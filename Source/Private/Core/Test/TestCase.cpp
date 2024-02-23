// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Test/TestCase.h"
#include "Test/TestManager.h"

#if ENGINE_TESTS_ALLOW_ANY

FTestCase::FTestCase()
	: bIsTestDone(false)
	, bAutoStartTest(true)
	, bAutoDeleteTest(true)
	, TestManager(nullptr)
{
}

FTestCase::~FTestCase()
{
}

bool FTestCase::IsTestDone() const
{
	return bIsTestDone;
}

bool FTestCase::ShouldAutoStartTest() const
{
	return bAutoStartTest;
}

void FTestCase::StartTest()
{
	LOG_DEBUG("Test nammed: '" << GetTestName() << "' starting ...");
	const size_t Nanosecond_Start = FUtil::GetNanoSeconds();
	
	DoTest();
	
	const size_t Nanosecond_End = FUtil::GetNanoSeconds();
	const size_t Nanosecond_TestDuration = Nanosecond_End - Nanosecond_Start;
	const std::string ActualTimeString = std::to_string(FUtil::NanoSecondToSecond<float>(Nanosecond_TestDuration));
	LOG_DEBUG("Test duration (nanoseconds): " + ActualTimeString + "s.");

	if (bAutoDeleteTest)
	{
		delete this;
		
		LOG_DEBUG("Test auto-deleted.");
	}
}

void FTestCase::DestroyTest()
{
}

char* FTestCase::GetTestName() const
{
	return TEXT_CHAR("Unnamed test case.");
}

void FTestCase::RegisterTest(FTestManager* InTestManager)
{
	TestManager = InTestManager;
}

void FTestCase::UnRegisterTest()
{
	if (TestManager != nullptr)
	{
		TestManager->RemoveTest(this);
	}
}

#endif
