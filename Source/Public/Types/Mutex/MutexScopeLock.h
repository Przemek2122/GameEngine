// Created by Przemys�aw Wiewi�ra 2024

#pragma once

#include "CoreMinimal.h"

class FMutex;

class FMutexScopeLock
{
public:
	FMutexScopeLock(FMutex& InMutex);
	~FMutexScopeLock();

protected:
	FMutex& Mutex;

};
