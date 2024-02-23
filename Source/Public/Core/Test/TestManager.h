// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"
#include "TestCase.h"

#if ENGINE_TESTS_ALLOW_ANY

/**
 * GEngine class used to check if things work properly.
 * Also can be used to see sample code.
 */
class FTestManager
{
public:
	FTestManager();
	virtual ~FTestManager();

	/** Creates Test by class. */
	template<class FTestCaseClass>
	FTestCaseClass* SpawnTestCaseByClass()
	{
		FTestCaseClass* NewTestCase = new FTestCaseClass();

		AddTest(NewTestCase);

		return NewTestCase;
	}

	/** Destroys all tests matching class. */
	template<class FTestCaseClass>
	void DestroyTestCaseByClass()
	{
		for (int i = 0; i < RunningTests.Size(); i++)
		{
			if (typeid(RunningTests[i]) == typeid(FTestCaseClass))
			{
				FTestCase* Test = RunningTests[i];
				
				RemoveTest(Test);

				delete Test;
			}
		}
	}

	virtual void AddTest(FTestCase* InTestCase, const bool bAutoStartTest = true);
	virtual void RemoveTest(FTestCase* InTestCase);
	
	virtual void Tick();
	virtual void Render();

protected:
	CArray<FTestCase*> RunningTests;
	
};

#endif
