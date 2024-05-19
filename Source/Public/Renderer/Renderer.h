// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"

class FTextureAsset;

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
	
	virtual void RepaintWindow();

	virtual void MarkNeedsRepaint();

public:
	_NODISCARD SDL_Renderer* GetSDLRenderer() const { return Renderer; }

	INLINE_DEBUGABLE SDL_Window* GetSdlWindow() const;

	INLINE_DEBUGABLE SDL_Surface* GetSdlWindowSurface() const;

	_NODISCARD FVector2D<int> GetWindowSize() const;

	void SetWindowSize(const int X, const int Y, const bool bUpdateSDL = true) const;

	void DrawTexture(const FTextureAsset* Texture, const FVector2D<int> Location, const FVector2D<int> Size) const;
	void DrawTexture(SDL_Texture* Texture, const FVector2D<int> Location, const FVector2D<int> Size) const;

	void DrawTextureAdvanced(const FTextureAsset* Texture, const FVector2D<int> Location, const FVector2D<int> Size, const int Rotation, const FVector2D<int> CenterOfRotation = FVector2D<int>(), SDL_RendererFlip Flip = SDL_RendererFlip::SDL_FLIP_NONE) const;
	void DrawTextureAdvanced(SDL_Texture* Texture, const FVector2D<int> Location, const FVector2D<int> Size, const int Rotation, const FVector2D<int> CenterOfRotation = FVector2D<int>(), SDL_RendererFlip Flip = SDL_RendererFlip::SDL_FLIP_NONE) const;

	static void OverrideTextureColor(SDL_Texture* Texture, const FColorRGBA& Color);
	static void OverrideTextureColorReset(SDL_Texture* Texture);

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

	void DrawLine(const FVector2D<int> From, const FVector2D<int> To) const;

protected:
	FWindow* Window;
	SDL_Renderer* Renderer;
	CDeque<FColorPoint> PointsToDrawDeque;
	bool bNeedsRepaint;

};
