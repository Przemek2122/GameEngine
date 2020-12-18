//

#include "CoreEngine.h"
#include "Renderer/Window.h"
#include "Renderer/Renderer.h"
#include <cmath> 

FWindow::FWindow(char* InTitle, const int InPositionX, const int InPositionY, const int InWidth, const int InHeight, const Uint32 InFlags)
	: WindowTitle(InTitle)
	, WindowPositionX(InPositionX)
	, WindowPositionY(InPositionY)
	, WindowWidth(InWidth)
	, WindowHeight(InHeight)
	, WindowFlags(InFlags)
{
	Window = SDL_CreateWindow(InTitle, InPositionX, InPositionY, InWidth, InHeight, InFlags);

	if (Window != nullptr)
	{
		LOG_INFO("Window created!");
	}
	else
	{
		LOG_ERROR("Can not create window: " << TEXT(SDL_GetError()));
		
		exit(-16);
	}

	Renderer = new FRenderer(Window);
}

FWindow::~FWindow()
{
	if (Window != nullptr)
	{
		SDL_DestroyWindow(Window);

		LOG_INFO("Window destroyed!");
	}
	else
	{
		LOG_WARN("Window not destroyed (pointer invalid)!");
	}

	delete Renderer;
}

void FWindow::Render()
{
	Renderer->PreRender();
	Renderer->Render();
	Renderer->PostRender();
}

void FWindow::Resize(const int NewWidth, const int NewHeight)
{
	SDL_SetWindowSize(Window, NewWidth, NewHeight);

	WindowWidth = NewWidth;
	WindowHeight = NewWidth;
}

FVector2D<int> FWindow::GetWindowSize() const
{
	FVector2D<int> Size;

	SDL_GetWindowSize(Window, &Size.X, &Size.Y);
	
	return Size;
}

FVector2D<float> FWindow::GetWindowSizePercent(const FVector2D<int> Position) const
{
	const auto Size = GetWindowSize();

	return (FVector2D<float>(Size) / FVector2D<float>(100)) * Position;
}
