//

#pragma once

#include "CoreMinimal.h"

/**
 * Base Renderer class.
 * Has SDL_Renderer.
 * Should only be created from FWindow class. 
 */
class FRenderer
{
friend FWindow;

protected:
	FRenderer(SDL_Window* InWindow);
	virtual ~FRenderer();

protected:
	SDL_Window* Window;

public:
	/** Before render - Clear scene */
	virtual void PreRender();

	/** Actual render - No need to call parent */
	virtual void Render();
	
	/** After render */
	virtual void PostRender();

protected:
	SDL_Renderer* Renderer;

};
