//

#include "CoreEngine.h"
#include "Renderer/Renderer.h"

FRenderer::FRenderer(SDL_Window* InWindow)
	: Window(InWindow)
{
	Renderer = SDL_CreateRenderer(InWindow, -1, 0);

	if (Renderer)
	{
		LOG_INFO("Renderer created!");
		
		SDL_SetRenderDrawColor(Renderer, 34, 91, 211, 255);
	}
	else
	{
		LOG_ERROR("Can not create renderer: " << TEXT(SDL_GetError()));
		
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
