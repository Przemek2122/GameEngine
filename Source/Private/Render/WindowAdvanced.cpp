//

#include <Engine.PCH.h>
#include "..\..\Public\Render\WindowAdvanced.h"
#include "..\..\Public\Render\Renderer.h"

FWindowAdanced::FWindowAdanced(char* InTitle, int InPositionX, int InPositionY, int InWidth, int InHeight, Uint32 InFlags)
	: FWindow(InTitle, InPositionX, InPositionY, InWidth, InHeight, InFlags)
{
}

FWindowAdanced::~FWindowAdanced()
{
}
