// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"

struct FColorPoint
{
	FColorPoint();
	FColorPoint(const FVector2D<int> InLocation, const FColorRGBA InColor);

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

protected:
	FWindow* Window;

public:
	/** Before render - Clear scene */
	virtual void PreRender();
	/** Gather render data */
	virtual void Render();
	/** After render - do render */
	virtual void PostRender();

	virtual void OnWindowSizeChanged();

protected:
	FVector2D<int> LastWindowSize;

public:
	/** Draw single point. */
	void DrawPointAt(const FColorPoint& ColorPoint) const;
	/** Draw multiple points with different colors (Use other overload if all colors all same). */
	void DrawPointsAt(const CArray<FColorPoint>& ColorPoints) const;
	/** Draw multiple points with same colors. */
	void DrawPointsAt(const CArray<FVector2D<int>>& Points, FColorRGBA& Color) const;

	void DrawCircle(const FVector2D<int> Location, const int Radius);
	void DrawLimitedLine(int x1, int y1, int x2, int y2, int lineLength);

protected:
	SDL_Renderer* Renderer;
	CDeque<FColorPoint> PointsToDrawDeque;

};
