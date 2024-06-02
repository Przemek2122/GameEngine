// Created by Przemys³aw Wiewióra 2024

#pragma once

#include "CoreMinimal.h"

class FMutex
{
public:
	FMutex();

	bool IsLocked() const;

	void Lock();
	void Unlock();

	bool TryLock();

protected:
	std::atomic_bool bIsLocked;
};
