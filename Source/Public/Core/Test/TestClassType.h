#pragma once

#include "CoreMinimal.h"
#include "Test/TestCase.h"

#if ENGINE_TESTS_ALLOW_ANY
class FTemporaryTestClass
{
public:
	FTemporaryTestClass()
	{
		LOG_INFO("Temporary test class created.");
	}

	~FTemporaryTestClass()
	{
		LOG_INFO("Temporary test class destroyed.");
	}

};

class FTestClassType : public FTestCase
{
public:
	void DoTest() override;

protected:
	FClassStorage<FTemporaryTestClass> StoredClass;

};

#endif // ENGINE_TESTS_ALLOW_ANY