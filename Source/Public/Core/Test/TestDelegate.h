// Created by Przemys�aw Wiewi�ra 2020

#pragma once

#include "CoreMinimal.h"

#if ENGINE_TESTS

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
	
};

#endif
