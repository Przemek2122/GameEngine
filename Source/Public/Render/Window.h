//

#pragma once

struct SDL_Window;
class FRenderer;

/**
 * Window class. Has SDL_Window and FRender.
 */
class FWindow
{
public:
	/**
	 * Creates SDL Window.
	 * Take a look here for avaiable flags (or at SDL_vide.h):
	 * https://wiki.libsdl.org/SDL_WindowFlags
	 */
	FWindow(char* InTitle, int InPositionX, int InPositionY, int InWidth, int InHeight, Uint32 InFlags = 0);
	virtual ~FWindow();

protected:
	SDL_Window* Window;
	FRenderer* Renderer;
	char* WindowTitle;
	int WindowPositionX;
	int WindowPositionY;
	int WindowWidth;
	int WindowHeight;
	Uint32 WindowFlags;
public:
	/**
	 * Render this window using renderer.
	 */
	virtual void Render();

public:
	/** Call to change window size. */
	void Resize(const int NewWidth, const int NewHeight);

};