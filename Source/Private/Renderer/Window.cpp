// Created by Przemys�aw Wiewi�ra 2020

#include "CoreEngine.h"
#include "Renderer/Window.h"
#include "ECS/EntityManager.h"
#include "Renderer/Renderer.h"
#include "Renderer/Map/MapManager.h"

FWindow::FWindow(char* InTitle, const int InPositionX, const int InPositionY, const int InWidth, const int InHeight, const Uint32 InFlags)
	: Window(SDL_CreateWindow(InTitle, InPositionX, InPositionY, InWidth, InHeight, InFlags))
	, WindowTitle(InTitle)
	, WindowPositionX(InPositionX)
	, WindowPositionY(InPositionY)
	, WindowWidth(InWidth)
	, WindowHeight(InHeight)
	, WindowFlags(InFlags)
	, bIsWindowFocused(false)
	, bIsWindowVisible(true)
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
	EntityManager = CreateEntityManager();
	MapManager = CreateMapManager();
}

void FWindow::ReceiveTick()
{
	if (bIsWindowVisible)
	{
		Tick();
	}
}

FWidgetManager* FWindow::CreateWidgetManager()
{
	return new FWidgetManager(this);
}

FEntityManager* FWindow::CreateEntityManager() const
{
	return new FEntityManager();
}

FMapManager* FWindow::CreateMapManager()
{
	return new FMapManager(this);
}

FRenderer* FWindow::CreateRenderer()
{
	return new FRenderer(this);
}

void FWindow::Tick()
{
	WidgetManager->TickWidgets();
}

void FWindow::Render()
{
	Renderer->PreRender();
	Renderer->Render();
	MapManager->DrawMap();
	WidgetManager->RenderWidgets();
	Renderer->PostRender();
}

void FWindow::SetWindowSize(const int X, const int Y, const bool bUpdateSDL)
{
	if (bUpdateSDL)
	{
		SDL_SetWindowSize(Window, X, Y);
	}

	WindowWidth = X;
	WindowHeight = Y;

	CArray<FWidget*> Widgets = WidgetManager->GetManagedWidgets();
	for (FWidget* Widget : Widgets)
	{
		Widget->OnWindowChanged();
	}
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

void FWindow::OnWindowMadeVisible()
{
	bIsWindowVisible = true;
}

void FWindow::OnWindowMadeInVisible()
{
	bIsWindowVisible = false;
}

void FWindow::OnWindowSizeChanged(const Sint32 X, const Sint32 Y)
{
	SetWindowSize(X, Y, false);
}

void FWindow::OnWindowLocationChanged(const Sint32 X, const Sint32 Y)
{
	SetWindowLocation(X, Y, false);
}

void FWindow::SetWindowFocus(const bool bInNewFocus)
{
	bIsWindowFocused = bInNewFocus;

	SDL_SetWindowInputFocus(Window);
}

FMapManager* FWindow::GetMapManager() const
{
	return MapManager;
}

FWidgetManager* FWindow::GetWidgetManager() const
{
	return WidgetManager;
}

FEntityManager* FWindow::GetEntityManager() const
{
	return EntityManager;
}
