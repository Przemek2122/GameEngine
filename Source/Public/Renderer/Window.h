// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"
#include "Widgets/WidgetManager.h"

class FWidgetManager;
class FWidget;

/**
 * Window class. Has SDL_Window and FRender.
 */
class FWindow
{
public:
	/**
	 * Creates SDL Window.
	 * Take a look here for available flags (or at SDL_vide.h):
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
	bool IsWindowFocused() const;
	void SetWindowFocus(const bool bInNewFocus);

protected:
	bool bIsWindowFocused;

public:
	/** Render this window using renderer. */
	virtual void Tick();
	/** Render this window using renderer. */
	virtual void Render();

protected:
	_NODISCARD virtual FRenderer* CreateRenderer() const;

public:
	/** Call to change window size. */
	void Resize(const int NewWidth, const int NewHeight);

	/** @returns Window size in px. */
	_NODISCARD FVector2D<int> GetWindowSize() const;
	/** @returns Window percent at given location. Window 100 with position 50 will be 0.5. */
	_NODISCARD FVector2D<float> GetWindowSizePercent(const FVector2D<int> Position) const;

protected:
	FWidgetManager* WidgetManager;
	_NODISCARD virtual FWidgetManager* CreateWidgetManager() const;

public:
	_NODISCARD INLINE_DEBUGABLE FWidgetManager* GetWidgetManager() const;
	
	template<class TWidgetTemplate>
	INLINE_DEBUGABLE FWidget& CreateWidget() const
	{
		return GetWidgetManager().CreateWidget<TWidgetTemplate>();
	}
	INLINE_DEBUGABLE bool DestroyWidget(FWidget* Widget) const
	{
		return GetWidgetManager()->DestroyWidget(Widget);
	}

};