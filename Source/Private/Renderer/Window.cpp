//

#include "Renderer/Window.h"
#include "Renderer/Renderer.h"
#include "CoreEngine.h"

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
		FUtil::Info("Window created!");
	}
	else
	{
		FUtil::Error("Can not create window: " + (std::string)SDL_GetError());
		exit(-16);
	}

	Renderer = new FRenderer(Window);
}

FWindow::~FWindow()
{
	if (Window != nullptr)
	{
		SDL_DestroyWindow(Window);

		FUtil::Info("Window destroyed!");
	}
	else
	{
		FUtil::Warn("Window not destroyed (pointer invalid)!");
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
