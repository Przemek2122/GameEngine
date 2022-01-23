// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Renderer/Window.h"

#include "ECS/EntityManager.h"
#include "Renderer/Renderer.h"

FWindow::FWindow(char* InTitle, const int InPositionX, const int InPositionY, const int InWidth, const int InHeight, const Uint32 InFlags)
	: Window(SDL_CreateWindow(InTitle, InPositionX, InPositionY, InWidth, InHeight, InFlags)), WindowTitle(InTitle)
	, WindowPositionX(InPositionX)
	, WindowPositionY(InPositionY)
	, WindowWidth(InWidth)
	, WindowHeight(InHeight)
	, WindowFlags(InFlags)
	, bIsWindowFocused(false)
{
	if (Window != nullptr)
	{
		LOG_INFO("Window created. (" << WindowTitle << ")");

		WindowId = SDL_GetWindowID(Window);
	}
	else
	{
		LOG_ERROR("Can not create window: " << STRING(SDL_GetError()) << " ! (" << WindowTitle << ")");
		
		exit(-16);
	}
}

FWindow::~FWindow()
{
	delete Renderer;	
	delete WidgetManager;

	if (Window != nullptr)
	{
		SDL_DestroyWindow(Window);

		LOG_INFO("Window destroyed. (" << WindowTitle << ")");
	}
	else
	{
		LOG_WARN("Window not destroyed (pointer invalid)! ("<< WindowTitle << ")");
	}
}

void FWindow::Init()
{
	Renderer = CreateRenderer();
	WidgetManager = CreateWidgetManager();
	EntityManager = GetEntityManager();
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
	WidgetManager->TickWidgets();

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
	WidgetManager->RenderWidgets();
	Renderer->PostRender();
}

FRenderer* FWindow::CreateRenderer()
{
	return new FRenderer(this);
}

void FWindow::SetWindowSize(const int X, const int Y, const bool bUpdateSDL)
{
	if (bUpdateSDL)
	{
		SDL_SetWindowSize(Window, X, Y);
	}

	WindowWidth = X;
	WindowHeight = Y;
}

void FWindow::SetWindowLocation(const int X, const int Y, const bool bUpdateSDL)
{
	if (bUpdateSDL)
	{
		SDL_SetWindowPosition(Window, X, Y);
	}

	WindowPositionX = X;
	WindowPositionY = Y;
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

FEntityManager* FWindow::CreateEntityManager() const
{
	return new FEntityManager();
}

FWidgetManager* FWindow::GetWidgetManager() const
{
	return WidgetManager;
}

FEntityManager* FWindow::GetEntityManager() const
{
	return EntityManager;
}
