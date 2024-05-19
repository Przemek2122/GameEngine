// Created by Przemys�aw Wiewi�ra 2024

#pragma once

#include "CoreMinimal.h"
#include "Test/TestBase.h"

/**
 * Any test which is not done within single function scope.
 * For example timers test where it's async.
 */
class FLongRunTest : public FTestBase
{
public:
	FLongRunTest();

	void StartTest() override;

	void EndTask();

	/** Test should be performed in this function. */
	virtual void InitializeTest() = 0;

};
