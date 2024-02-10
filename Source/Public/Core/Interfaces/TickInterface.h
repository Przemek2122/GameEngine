#pragma once

#include "CoreMinimal.h"

/**
 * Class for objects that need to be ticked
 * Self registers and unregisters
 */
class FTickInterface
{
public:
	FTickInterface();
	virtual ~FTickInterface();

	virtual void Tick(float DeltaTime) = 0;

};
