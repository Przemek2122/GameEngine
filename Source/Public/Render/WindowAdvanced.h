//

#pragma once

#include "Window.h"

struct SDL_Window;
class FRenderer;

/**
 * Advanced window
 */
class FWindowAdanced : public FWindow
{
public:
	FWindowAdanced(char* InTitle, int InPositionX, int InPositionY, int InWidth, int InHeight, Uint32 InFlags = 0);
	virtual ~FWindowAdanced();

protected:

};