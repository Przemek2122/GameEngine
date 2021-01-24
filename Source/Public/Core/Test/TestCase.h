// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"

#if ENGINE_TESTS

/**
 * Base class for testing.
 * Do once test.
 */
class FTestCase
{
public:
	FTestCase();
	virtual ~FTestCase();

	_NODISCARD bool IsTestDone() const;
	_NODISCARD bool ShouldAutoStartTest() const;

	/** Called once added into manager. */
	void StartTest();
	/** Test should be performed in this function. */
	virtual void DoTest() = 0;
	
	virtual char* GetTestName() const;

protected:
	bool bIsTestDone;
	bool bAutoStartTest;
	bool bAutoDeleteTest;
	
};

#endif
