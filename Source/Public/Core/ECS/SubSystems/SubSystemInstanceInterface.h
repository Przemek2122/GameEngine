// Created by Przemys�aw Wiewi�ra 2024

#pragma once

#include "CoreMinimal.h"

class ISubSystemManagerInterface;

/**
 * Interface for any object which should be subsystem
 */
class ISubSystemInstanceInterface
{
public:
	ISubSystemInstanceInterface();
	virtual ~ISubSystemInstanceInterface();

	void SetSubSystemManager(ISubSystemManagerInterface* InSubSystemParentInterface, const bool bAutoInit = true);

	virtual void InitializeSubSystem();
	virtual void TickSubSystem();
	virtual void RenderSubSystem();

	ISubSystemManagerInterface* GetSubSystemParentInterface() const { return SubSystemParentInterface; }

private:
	ISubSystemManagerInterface* SubSystemParentInterface;

};
