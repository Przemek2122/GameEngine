// Created by Przemys�aw Wiewi�ra 2020

#include "CoreEngine.h"
#include "Test/TestManager.h"

#if ENGINE_TESTS_ALLOW_ANY

FTestManager::FTestManager()
{
}

FTestManager::~FTestManager()
{
}

void FTestManager::AddTest(FTestCase* InTestCase, const bool bAutoStartTest)
{
	if (InTestCase != nullptr)
	{
		if (bAutoStartTest && !InTestCase->IsTestDone() && InTestCase->ShouldAutoStartTest())
		{
			InTestCase->StartTest();
		}
		
		InTestCase->RegisterTest(this);
		RunningTests.Push(InTestCase);	
	}
}

void FTestManager::RemoveTest(FTestCase* InTestCase)
{
	RunningTests.Remove(InTestCase);
}

void FTestManager::Tick()
{
	/*
	const auto TestsNum = static_cast<unsigned int>(RunningTests.Size());
	
	for ( unsigned int i = 0; i < TestsNum; i++)
	{
		RunningTests[i]->Tick();
	}
	*/
}

void FTestManager::Render()
{
	/*
	const auto TestsNum = static_cast<unsigned int>(RunningTests.Size());
	
	for ( unsigned int i = 0; i < TestsNum; i++)
	{
		RunningTests[i]->Render();
	}
	*/
}

#endif
