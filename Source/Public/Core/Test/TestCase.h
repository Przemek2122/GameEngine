// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"

#if ENGINE_TESTS_ALLOW_ANY

class FTestManager;

/**
 * Base class for testing.
 * Do once test.
 */
class FTestCase
{
	friend FTestManager;
	
public:
	FTestCase();
	virtual ~FTestCase();

	_NODISCARD bool IsTestDone() const;
	_NODISCARD bool ShouldAutoStartTest() const;

	/** Called once added into manager. */
	void StartTest();
	/** Test should be performed in this function. */
	virtual void DoTest() = 0;

	void DestroyTest();
	
	_NODISCARD virtual char* GetTestName() const;

protected:
	void RegisterTest(FTestManager* InTestManager);
	void UnRegisterTest();

protected:
	bool bIsTestDone;
	bool bAutoStartTest;
	bool bAutoDeleteTest;

	FTestManager* TestManager;
	
};

#endif
