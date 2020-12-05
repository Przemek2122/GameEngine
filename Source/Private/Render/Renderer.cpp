//

#include <Engine.PCH.h>
#include "Renderer.h"

FRenderer::FRenderer(SDL_Window* InWindow)
	: Window(InWindow)
{
	Renderer = SDL_CreateRenderer(InWindow, -1, 0);

	if (Renderer)
	{
		FUtil::Info("Renderer created!");
		SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
	}
	else
	{
		FUtil::Error("Can not create renderer: " + (std::string)SDL_GetError());
		exit(-32);
	}
}

FRenderer::~FRenderer()
{
	SDL_DestroyRenderer(Renderer);
}

void FRenderer::PreRender()
{
	SDL_RenderClear(Renderer);
}

void FRenderer::Render()
{
}

void FRenderer::PostRender()
{
	SDL_SetRenderDrawColor(Renderer, 100, 100, 100, 255); // Background color
	SDL_RenderPresent(Renderer);
}
