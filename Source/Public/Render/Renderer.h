//

#pragma once

struct SDL_Renderer;
struct SDL_Window;
class FWindow;

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
	SDL_Renderer* Renderer;
	SDL_Window* Window;

public:
	/** Before render - Clear scene */
	void PreRender();

	/** Actual render */
	void Render();
	
	/** After render */
	void PostRender();

protected:

};
