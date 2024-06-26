// Created by Przemys�aw Wiewi�ra 2024

#include "CoreEngine.h"
#include "Test/TestLongRun.h"

FLongRunTest::FLongRunTest()
{
	bAutoDeleteTest = false;
}

void FLongRunTest::StartTest()
{
	FTestBase::StartTest();

	LOG_DEBUG(GetTestName() << " - Long run test starting ...");

	InitializeTest();

	if (bAutoDeleteTest)
	{
		DestroyTest();
	}
}

void FLongRunTest::EndTask()
{
	LOG_DEBUG(GetTestName() << " - finished.");

	DestroyTest();
}
