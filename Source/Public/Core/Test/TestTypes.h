// Created by Przemys�aw Wiewi�ra 2020

#pragma once

#include "CoreMinimal.h"
#include "TestCase.h"

#if ENGINE_TESTS_ALLOW_ANY

class FTestTypes : public FTestCase
{
public:
	void DoTest() override;

	_NODISCARD char* GetTestName() const override;
		
};

#endif
