// Created by Przemys�aw Wiewi�ra 2024

#pragma once

#include "CoreMinimal.h"

/**
 * Interface for any object which should be subsystem
 */
class ISubSystemInstanceInterface
{
public:
	ISubSystemInstanceInterface(ISubSystemParentInterface* InSubSystemParentInterface);
	virtual ~ISubSystemInstanceInterface();

	void TickSubSystem();

protected:
	ISubSystemParentInterface* SubSystemParentInterface;

};
