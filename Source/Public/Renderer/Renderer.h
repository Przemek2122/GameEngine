// Created by Przemys�aw Wiewi�ra 2020

#pragma once

#include "CoreMinimal.h"

struct FColorPoint
{
	FColorPoint();
	FColorPoint(const FVector2D<int> InLocation, const FColorRGBA& InColor);

	FVector2D<int> Location;
	FColorRGBA Color;
};

/**
 * Base Renderer class.
 * Has SDL_Renderer.
 * Should only be created from FWindow class. 
 */
class FRenderer
{
friend FWindow;

protected:
	FRenderer(FWindow* InWindow);
	virtual ~FRenderer();
	
	/** Before render - Clear scene */
	virtual void PreRender();
	/** Gather render data */
	virtual void Render();
	/** After render - do render */
	virtual void PostRender();

	virtual void PaintDefaultBackground();

	virtual void Repaint();
	
	virtual void RepaintWindowToSize(const SDL_Rect& ViewportSize);

public:
	_NODISCARD SDL_Renderer* GetSDLRenderer() const { return Renderer; }
	INLINE_DEBUGABLE SDL_Window* GetSdlWindow() const;
	INLINE_DEBUGABLE SDL_Surface* GetSdlWindowSurface() const;
	_NODISCARD FVector2D<int> GetWindowSize() const;
	void SetWindowSize(const FVector2D<int> NewWindowSize, const bool bUpdateSDL = true) const;

protected:
	FWindow* Window;
	SDL_Renderer* Renderer;
	CDeque<FColorPoint> PointsToDrawDeque;
	bool bNeedsRepaint;

public:
	/** Draw single point. */
	void DrawPointAt(const FColorPoint& ColorPoint) const;
	/** Draw multiple points with same colors. */
	void DrawPointsAt(const CArray<FVector2D<int>>& Points, const FColorRGBA& AllPointsColor) const;
	/** Draw multiple points with same colors. */
	void DrawPointsAt(const CArray<SDL_Point>& Points, const FColorRGBA& AllPointsColor) const;

	/** Draw single rectangle */
	void DrawRectangle(const FVector2D<int> RectLocation, const FVector2D<int> RectSize, const FColorRGBA& InColor) const;
	/** Draw single rectangle but without interior */
	void DrawRectangleOutline(const FVector2D<int> RectLocation, const FVector2D<int> RectSize, const FColorRGBA& InColor) const;
	
	void DrawCircle(const FVector2D<int> Location, const int Radius) const;
	void DrawLimitedLine(int X1, int Y1, int X2, int Y2, int LineLength) const;

};
