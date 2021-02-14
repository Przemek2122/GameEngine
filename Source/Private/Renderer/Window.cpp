// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Renderer/Window.h"
#include "Renderer/Renderer.h"

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
		LOG_INFO("Window created. (" << WindowTitle << ")");
	}
	else
	{
		LOG_ERROR("Can not create window: " << STRING(SDL_GetError()) << " ! (" << WindowTitle << ")");
		
		exit(-16);
	}
	
	Renderer = CreateRenderer();
	WidgetManager = CreateWidgetManager();
}

FWindow::~FWindow()
{
	if (Window != nullptr)
	{
		SDL_DestroyWindow(Window);

		LOG_INFO("Window destroyed. (" << WindowTitle << ")");
	}
	else
	{
		LOG_WARN("Window not destroyed (pointer invalid)! ("<< WindowTitle << ")");
	}

	delete Renderer;	
	delete WidgetManager;
}

SDL_Window* FWindow::GetSdlWindow() const
{
	return Window;
}

bool FWindow::IsWindowFocused() const
{
	return bIsWindowFocused;
}

void FWindow::SetWindowFocus(const bool bInNewFocus)
{
	bIsWindowFocused = bInNewFocus;
	
	SDL_SetWindowInputFocus(Window);
}

void FWindow::OnWindowFocusReceive()
{
	LOG_DEBUG("FOCUS " << IsWindowFocused());
}

void FWindow::OnWindowFocusLost()
{
	LOG_DEBUG("FOCUS " << IsWindowFocused());
}

void FWindow::ReceiveTick()
{
	Tick();
}

void FWindow::Tick()
{
	WidgetManager->Tick();

	const Uint32 SdlWindowFlags = SDL_GetWindowFlags(Window);

	WindowFlags = SdlWindowFlags;

	// Has focus  SDL_WINDOW_INPUT_FOCUS SDL_WINDOW_INPUT_GRABBED SDL_WINDOW_MOUSE_FOCUS
	if (BITMASK_IS_SET(SdlWindowFlags, SDL_WINDOW_MOUSE_FOCUS))
	{
		if (!IsWindowFocused())
		{
			bIsWindowFocused = true;

			OnWindowFocusReceive();
		}
	}
	// Do not have focus
	else
	{
		if (IsWindowFocused())
		{
			bIsWindowFocused = false;

			OnWindowFocusLost();
		}
	}
}

void FWindow::Render()
{
	Renderer->PreRender();
	Renderer->Render();
	WidgetManager->Render();
	Renderer->PostRender();
}

FRenderer* FWindow::CreateRenderer()
{
	return new FRenderer(this);
}

void FWindow::Resize(const int NewWidth, const int NewHeight)
{
	SDL_SetWindowSize(Window, NewWidth, NewHeight);

	WindowWidth = NewWidth;
	WindowHeight = NewWidth;
}

FRenderer* FWindow::GetRenderer() const
{
	return Renderer;
}

FVector2D<int> FWindow::GetWindowSize() const
{
	FVector2D<int> Size;

	SDL_GetWindowSize(Window, &Size.X, &Size.Y);
	
	return Size;
}

FVector2D<float> FWindow::GetWindowSizePercent(const FVector2D<int> Position) const
{
	const FVector2D<int> WindowSize = GetWindowSize();

	return (FVector2D<float>(WindowSize) / FVector2D<float>(100)) * Position;
}

FVector2D<int> FWindow::GetWindowLocation() const
{
	FVector2D<int> WindowLocation;
	
	SDL_GetWindowPosition(Window, &WindowLocation.X, &WindowLocation.Y);

	return WindowLocation;
}

FWidgetManager* FWindow::CreateWidgetManager()
{
	return new FWidgetManager(this);
}

FWidgetManager* FWindow::GetWidgetManager() const
{
	return WidgetManager;
}
