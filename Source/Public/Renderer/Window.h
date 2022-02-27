// See https://github.com/Przemek2122/GameEngine

#pragma once

#include "CoreMinimal.h"
#include "Widgets/WidgetManager.h"

class FEntityManager;
class FWidgetManager;
class FWidget;

/**
 * Window class. Has SDL_Window and FRender.
 */
class FWindow
{
	friend FEngineRender;

protected:
	/**
	 * Creates SDL Window.
	 * Take a look here for available flags (or at SDL_vide.h): https://wiki.libsdl.org/SDL_WindowFlags
	 */
	FWindow(char* InTitle, int InPositionX, int InPositionY, int InWidth, int InHeight, Uint32 InFlags = SDL_WINDOW_RESIZABLE);
	virtual ~FWindow();

	virtual void Init();

public:
	_NODISCARD SDL_Window* GetSdlWindow() const { return Window; }
	_NODISCARD Uint32 GetWindowId() const { return WindowId; }

protected:
	SDL_Window* Window;
	FRenderer* Renderer{};
	char* WindowTitle;
	int WindowPositionX;
	int WindowPositionY;
	int WindowWidth;
	int WindowHeight;
	Uint32 WindowFlags;
	Uint32 WindowId;

public:
	_NODISCARD bool IsWindowFocused() const { return bIsWindowFocused; }
	void SetWindowFocus(const bool bInNewFocus);

protected:
	bool bIsWindowFocused;
	bool bIsWindowVisible;

protected:
	void ReceiveTick();

public:
	/** Render this window using renderer. */
	virtual void Tick();
	/** Render this window using renderer. */
	virtual void Render();

protected:
	_NODISCARD virtual FRenderer* CreateRenderer();

public:
	/** Call to change window size. */
	void SetWindowSize(const int X, const int Y, const bool bUpdateSDL = true);
	
	/** Call to change window location. */
	void SetWindowLocation(const int X, const int Y, const bool bUpdateSDL);

	_NODISCARD FRenderer* GetRenderer() const;

	/** @returns Window size in px. */
	_NODISCARD FVector2D<int> GetWindowSize() const;
	/** @returns Window percent at given location. Window { 100, 200 } with position { 50, 50 } will be { 0.5, 0.25 }. */
	_NODISCARD FVector2D<float> GetWindowSizePercent(const FVector2D<int> Position) const;

	_NODISCARD FVector2D<int> GetWindowLocation() const;

	virtual void OnWindowMadeVisible();
	virtual void OnWindowMadeInVisible();

	virtual void OnWindowSizeChanged(Sint32 X, Sint32 Y);
	virtual void OnWindowLocationChanged(Sint32 X, Sint32 Y);

protected:
	FWidgetManager* WidgetManager{};
	FEntityManager* EntityManager{};
	
protected:
	_NODISCARD virtual FWidgetManager* CreateWidgetManager();
	_NODISCARD virtual FEntityManager* CreateEntityManager() const;

public:
	_NODISCARD FWidgetManager* GetWidgetManager() const;
	_NODISCARD FEntityManager* GetEntityManager() const;
	
	template<class TWidgetTemplate>
	_NODISCARD FWidget& CreateWidget() const
	{
		return GetWidgetManager().CreateWidget<TWidgetTemplate>();
	}
	bool DestroyWidget(FWidget* Widget) const
	{
		return GetWidgetManager()->DestroyWidget(Widget);
	}

};