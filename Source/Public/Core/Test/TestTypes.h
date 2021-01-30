// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"
#include "TestCase.h"

#if ENGINE_TESTS

class FTestTypes : public FTestCase
{
public:
	void DoTest() override;

	_NODISCARD char* GetTestName() const override;
		
};

#endif
