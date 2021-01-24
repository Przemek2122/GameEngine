// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Test/TestTypes.h"
#include "FunctorStatic.h"

void TestStaticFunction(void())
{
	LOG_DEBUG("Static function called!");
}

void TestStaticFunctionWithParameters(int Test)
{
	LOG_DEBUG("Static function called! Test int: " << Test);
}

void FTestTypes::DoTest()
{
	auto TestLambda = [&] (void())
	{
		LOG_DEBUG("Lambda called!");
	};
	
	FFunctorStatic<void> FunctorTest(TestStaticFunction);
	FunctorTest();
	FFunctorStatic<void, int> FunctorTestWithParameters(TestStaticFunctionWithParameters);
	FunctorTestWithParameters(2);
	//FFunctorStatic<void> FunctorTestLambda(TestLambda);
	//FunctorTestLambda();
}

char* FTestTypes::GetTestName() const
{
	return TEXT("FTestTypes");
}
