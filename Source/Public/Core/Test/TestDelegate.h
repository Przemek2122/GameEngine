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
	void TestFirstDelegate();
	void TestSecondDelegate();
	void TestThirdDelegate();
	void TestFirstSafeDelegate();

protected:
	FDelegate<> OnFirstDelegate;
	FDelegate<void, int> OnSecondDelegate;
	FDelegate<void, int, float> OnThirdDelegate;
	FDelegateSafe<void, int, float> OnFirstSafeDelegate;
	
};

#endif
