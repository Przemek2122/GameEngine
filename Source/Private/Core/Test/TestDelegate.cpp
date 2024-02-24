// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Test/TestDelegate.h"

#if ENGINE_TESTS_ALLOW_ANY

void FTestDelegate::DoTest()
{
	{
		// Or auto
		FFunctorLambda<void>* Lambda = new FFunctorLambda<void>(
		[]
		{
			LOG_DEBUG("Test#1 lambda called");
		});

		OnTestDelegateOne.BindLambda(Lambda);
	}

	{
		auto Lambda2 = []
		{
			LOG_DEBUG("Test#2 lambda inline called");
		};
		
		OnTestDelegateOne.BindLambda(Lambda2);
	}

	{
		OnTestDelegateOne.BindLambda(new FFunctorLambda<void>(
		[]
		{
			LOG_DEBUG("Test#3 lambda inline called");
		}));
	}
	
	{
		OnTestDelegateOne.BindLambda(
		[]
		{
			LOG_DEBUG("Test#4 lambda inline 2 called");
		});
	}

	// Finally call all bound delegate functions.
	OnTestDelegateOne.Execute();

	{
		OnTestDelegateTwo.BindLambda(
		[] (int Test)
		{
			LOG_DEBUG("Test#4 lambda inline 2 called with int: " << Test);
		});
	}
	
	OnTestDelegateTwo.Execute(234);

	{
		OnTestDelegateThree.BindLambda(
		[] (int Test, float Test2)
		{
			LOG_DEBUG("Test#4 lambda inline 2 called with int: " << Test << " and float: " << Test2);
		});
	}

	OnTestDelegateThree.Execute(545, 5.5f);
}

char* FTestDelegate::GetTestName() const
{
	return TEXT_CHAR("FTestDelegate");
}

#endif
