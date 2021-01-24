// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Test/TestCase.h"

FTestCase::FTestCase()
	: bIsTestDone(false)
	, bAutoStartTest(true)
	, bAutoDeleteTest(true)
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
	LOG_DEBUG("StartTest() - Test nammed: '" << GetTestName() << "' starting ...");
	const auto Nanosecond_Start = FUtil::GetNanoSeconds();
	LOG_DEBUG("Test start (nanoseconds): " << std::to_string(Nanosecond_Start).c_str());
	
	DoTest();
	
	const auto Nanosecond_End = FUtil::GetNanoSeconds();
	LOG_DEBUG("Test end (nanoseconds): " << std::to_string(Nanosecond_End).c_str());
	const auto Nanosecond_TestDuration = Nanosecond_End - Nanosecond_Start;
	LOG_DEBUG("Test duration (nanoseconds): " << std::to_string(Nanosecond_TestDuration).c_str());

	if (bAutoDeleteTest)
	{
		delete this;
		
		LOG_DEBUG("Test auto-deleted.");
	}
}

char* FTestCase::GetTestName() const
{
	return TEXT("Unnamed test case.");
}
