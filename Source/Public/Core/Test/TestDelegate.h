// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"
#include "DelegateSafe.h"

#if ENGINE_TESTS_ALLOW_ANY

#include "Test/TestCase.h"

class FTestDelegate : public FTestCase
{
public:
	void DoTest() override;

	_NODISCARD char* GetTestName() const override;

protected:
	FDelegate<> OnTestDelegateOne;
	FDelegate<void, int> OnTestDelegateTwo;
	FDelegate<void, int, float> OnTestDelegateThree;
	FDelegateSafe<void, int, float> DelegateSafeTest;
	
};

#endif
