// See https://github.com/Przemek2122/GameEngine

#pragma once

#include "CoreMinimal.h"
#include "Widgets/WidgetManager.h"

class FEntityManager;
class FWidgetInputManager;
class FWidgetManager;
class FWidget;

#define WINDOW_DEFAULT_FLAGS (SDL_WINDOW_RESIZABLE)

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
	FWindow(char* InTitle, int InPositionX, int InPositionY, int InWidth, int InHeight, Uint32 InFlags = WINDOW_DEFAULT_FLAGS);
	virtual ~FWindow();

	virtual void Init();
	virtual void DeInit();

	void ReceiveTick();

	_NODISCARD virtual FWidgetManager* CreateWidgetManager();
	_NODISCARD virtual FWidgetInputManager* CreateWidgetInputManager();
	_NODISCARD virtual FMapManager* CreateMapManager();

	_NODISCARD virtual FRenderer* CreateRenderer();

public:
	/** Render this window using renderer. */
	virtual void Tick();
	/** Render this window using renderer. */
	virtual void Render();

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

	_NODISCARD SDL_Window* GetSdlWindow() const { return Window; }

	_NODISCARD Uint32 GetWindowId() const { return WindowId; }

	_NODISCARD bool IsWindowFocused() const { return bIsWindowFocused; }
	void SetWindowFocus(const bool bInNewFocus);

	_NODISCARD FMapManager* GetMapManager() const;

	/** Use this if you changed to your own. Will return casted. */
	template<typename TMapManagerClass>
	TMapManagerClass* GetMapManager() const
	{
		return static_cast<TMapManagerClass>(GetMapManager());
	}

	_NODISCARD FWidgetManager* GetWidgetManager() const;
	_NODISCARD FWidgetInputManager* GetWidgetInputManager() const;

	template<class TWidgetTemplate>
	_NODISCARD TWidgetTemplate* CreateWidget() const
	{
		return GetWidgetManager()->CreateWidget<TWidgetTemplate>();
	}
	bool DestroyWidget(FWidget* Widget) const
	{
		return GetWidgetManager()->DestroyChildWidget(Widget);
	}

protected:
	SDL_Window* Window;
	FRenderer* Renderer;
	char* WindowTitle;
	int WindowPositionX;
	int WindowPositionY;
	int WindowWidth;
	int WindowHeight;
	Uint32 WindowFlags;
	Uint32 WindowId;

	bool bIsWindowFocused;
	bool bIsWindowVisible;

	FWidgetManager* WidgetManager;
	FWidgetInputManager* WidgetInputManager;

	FMapManager* MapManager;

};