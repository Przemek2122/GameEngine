// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Test/TestTypes.h"
#include "FunctorLambda.h"
#include "FunctorObject.h"
#include "FunctorStatic.h"

#if ENGINE_TESTS

void TestStaticFunction()
{
	LOG_DEBUG("(Static #A) FFunctorStatic<void> function called however it does noting now...");
}

void TestStaticFunctionWithParameters(int InTestInt)
{
	LOG_DEBUG("(Static #B) FFunctorStatic<void, int> Test int: " << InTestInt);
}

double TestStaticFunctionWithParameters(int InTestInt, float InTestFloat)
{
	LOG_DEBUG("(Static #C) FFunctorStatic<double, int, float> InTestInt: " << InTestInt << " InTestFloat: " << InTestFloat);

	return 0.5;
}

class FTestTypesObjectA
{
public:
	void Test()
	{
		LOG_DEBUG("(Object #A) TestTypesObjectA::Test() ");
	}
	
};

void FTestTypes::DoTest()
{
	// Static functions
	{
		// Usage:
		// FFunctorStatic<TReturnType, TInParams ...>
		// First is return type rest are function parameters

		LOG_DEBUG("(Test static functions)");
		
		// static function
		{
			FFunctorStatic FunctorTest(TestStaticFunction);
			FunctorTest();	
		}
		
		// static function with parameter
		{
			FFunctorStatic<void, int> FunctorTestWithParameters(TestStaticFunctionWithParameters);
			FunctorTestWithParameters(2);
		}
		
		// static function with return type and 2 parameters
		{
			FFunctorStatic<double, int, float> FunctorTestWithParameters(TestStaticFunctionWithParameters);
			
			LOG_DEBUG("(Static #C) returned: " << FunctorTestWithParameters(2, 3.f));
		}
	}

	// Lambda
	{
		// Usage:
		// Lambdas should be left for C++ Class template argument deduction
		// First is return type rest are function parameters
		
		LOG_DEBUG("(Test lambda)");
		
		// Using std::function for temporary storage or copy
		{
			std::function TestLambda1([]() 
			{ 
				LOG_DEBUG("(Lambda #A) FFunctorLambda function called however it does noting now...");
			});
			
			FFunctorLambda TestLambda(TestLambda1);

			TestLambda();
		}
		
		// Using std::function as converter
		{
			FFunctorLambda TestLambda2(std::function([]() 
			{
				LOG_DEBUG("(Lambda #B) FFunctorLambda function called however it does noting now...");
			}));

			TestLambda2();
		}
		
		// Using lambda parameters
		{
			FFunctorLambda TestLambda3(std::function([](int Test, double TestTwo) 
			{
				LOG_DEBUG("(Lambda #C) FFunctorLambda Test: " << Test << " TestTwo: " << TestTwo);
			}));

			TestLambda3(3, 5.1);
		}

		LOG_DEBUG("(Test lambda inline)");
		LOG_DEBUG("(Currently do not work)");
		
		// Using inline lambda
		{
			/*
			FFunctorLambda([]() 
			{
				LOG_DEBUG("(Example #5) FFunctorLambda function called!");
			});
			*/
		}

		// Another inline lambda
		/*
		{
			auto TestLambda = [&] () -> void
			{
				LOG_DEBUG("Lambda called!");
			};

			FFunctorLambda(TestLambda);
		}
		*/
	}

	// Function on object
	{
		LOG_DEBUG("(Functions in objects)");
		
		FTestTypesObjectA TestTypesObjectA;
		
		FFunctorObject FunctorObject(&TestTypesObjectA, &FTestTypesObjectA::Test);

		if (FunctorObject.IsValid())
		{
			FunctorObject();
		}
	}
}

char* FTestTypes::GetTestName() const
{
	return TEXT("FTestTypes");
}

#endif
