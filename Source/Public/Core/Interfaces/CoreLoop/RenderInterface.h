#pragma once

#include "CoreMinimal.h"

/**
 * Class for objects that need to be ticked
 * Self registers and unregisters
 */
class FRenderInterface
{
public:
	FRenderInterface();
	virtual ~FRenderInterface();

	virtual void Draw(float DeltaTime) = 0;

};
