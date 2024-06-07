// Created by Przemys�aw Wiewi�ra 2024

#pragma once

#include "CoreMinimal.h"

class FMutex
{
public:
	FMutex();

	bool IsLocked() const;

	void Lock();
	void Unlock();

	/** Will try to lock mutex, will return false if locked already, true if succesfuly locked */
	bool TryLock();

protected:
	bool bIsLocked;

};
