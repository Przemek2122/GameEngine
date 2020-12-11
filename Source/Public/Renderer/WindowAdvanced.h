//

#pragma once

#include "CoreMinimal.h"

/**
 * Advanced window
 */
class FWindowAdvanced : public FWindow
{
public:
	FWindowAdvanced(char* InTitle, int InPositionX, int InPositionY, int InWidth, int InHeight, Uint32 InFlags = 0);
	virtual ~FWindowAdvanced();

protected:

};