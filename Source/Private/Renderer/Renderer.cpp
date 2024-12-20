// See https://github.com/Przemek2122/GameEngine

#include "CoreEngine.h"
#include "Renderer/Renderer.h"

#include "Assets/Assets/TextureAsset.h"

FColorPoint::FColorPoint()
	: Location(0)
	, Color(0)
{
}

FColorPoint::FColorPoint(const FVector2D<int> InLocation, const FColorRGBA& InColor)
	: Location(InLocation)
	, Color(InColor)
{
}

FRenderer::FRenderer(FWindow* InWindow)
	: Window(InWindow)
	, Renderer(SDL_CreateRenderer(InWindow->GetSdlWindow(), -1, SDL_RendererFlags::SDL_RENDERER_ACCELERATED))
	, bNeedsRepaint(false)
{
	if (Renderer)
	{
		LOG_INFO("Renderer created!");

		SDL_SetRenderDrawColor(Renderer, 34, 91, 211, 255);
	}
	else
	{
		LOG_ERROR("Can not create renderer: " << STRING(SDL_GetError()));

		exit(-32);
	}
}

FRenderer::~FRenderer()
{
	// @TODO Crashes when exiting
	//SDL_DestroyRenderer(Renderer);
}

void FRenderer::PreRender()
{
	if (bNeedsRepaint)
	{
		Repaint();
	}
	
	SDL_RenderClear(Renderer);
}

void FRenderer::Render()
{
	while (!PointsToDrawDeque.IsEmpty())
	{
		const FColorPoint& ColorPoint = PointsToDrawDeque.PeekFirst();
		
		SDL_SetRenderDrawColor(Renderer, ColorPoint.Color.R, ColorPoint.Color.G, ColorPoint.Color.B, ColorPoint.Color.A);
		SDL_RenderDrawPoint(Renderer, ColorPoint.Location.X, ColorPoint.Location.Y);

		PointsToDrawDeque.DequeFront();
	}
}

void FRenderer::PostRender()
{
	PaintDefaultBackground();

	SDL_RenderPresent(Renderer);
}

void FRenderer::PaintDefaultBackground()
{
	SDL_SetRenderDrawColor(Renderer, 34, 34, 34, 255); // Background color
}

void FRenderer::Repaint()
{
	RepaintWindow();
}

void FRenderer::RepaintWindow()
{
    SDL_UpdateWindowSurface(GetSdlWindow());
}

void FRenderer::MarkNeedsRepaint()
{
	bNeedsRepaint = true;
}

SDL_Window* FRenderer::GetSdlWindow() const
{
	return Window->GetSdlWindow();
}

SDL_Surface* FRenderer::GetSdlWindowSurface() const
{
	return SDL_GetWindowSurface(Window->GetSdlWindow());
}

FVector2D<int> FRenderer::GetWindowSize() const
{
	return Window->GetWindowSize();
}

void FRenderer::SetWindowSize(const int X, const int Y, const bool bUpdateSDL) const
{
	Window->SetWindowSize(X, Y, bUpdateSDL);
}

void FRenderer::DrawTexture(const FTextureAsset* Texture, const FVector2D<int> Location, const FVector2D<int> Size, const bool bIsLocationRelative) const
{
	DrawTexture(Texture->GetTexture()->GetSDLTexture(), Location, Size, bIsLocationRelative);
}

void FRenderer::DrawTexture(SDL_Texture* Texture, FVector2D<int> Location, const FVector2D<int> Size, const bool bIsLocationRelative) const
{
	if (bIsLocationRelative)
	{
		Location = ConvertLocationToScreenSpace(Location);
	}

	SDL_Rect Rect;
	Rect.x = Location.X;
	Rect.y = Location.Y;
	Rect.w = Size.X;
	Rect.h = Size.Y;

	SDL_RenderCopy(Renderer, Texture, nullptr, &Rect);
}

void FRenderer::DrawTextureAdvanced(const FTextureAsset* Texture, const FVector2D<int> Location, const FVector2D<int> Size, const int Rotation, const FVector2D<int> CenterOfRotation, SDL_RendererFlip Flip, const bool bIsLocationRelative) const
{
	DrawTextureAdvanced(Texture->GetTexture()->GetSDLTexture(), Location, Size, Rotation, CenterOfRotation, Flip, bIsLocationRelative);
}

void FRenderer::DrawTextureAdvanced(SDL_Texture* Texture, FVector2D<int> Location, const FVector2D<int> Size, const int Rotation, const FVector2D<int> CenterOfRotation, SDL_RendererFlip Flip, const bool bIsLocationRelative) const
{
	if (bIsLocationRelative)
	{
		Location = ConvertLocationToScreenSpace(Location);
	}

	SDL_Rect Rect;
	Rect.x = Location.X;
	Rect.y = Location.Y;
	Rect.w = Size.X;
	Rect.h = Size.Y;

	SDL_RenderCopyEx(Renderer, Texture, nullptr, &Rect, Rotation, CenterOfRotation, Flip);
}

void FRenderer::OverrideTextureColor(SDL_Texture* Texture, const FColorRGBA& Color)
{
	SDL_SetTextureColorMod(Texture, Color.R, Color.G, Color.B);
}

void FRenderer::OverrideTextureColorReset(SDL_Texture* Texture)
{
	static FColorRGBA Color = FColorRGBA::ColorWhite();

	SDL_SetTextureColorMod(Texture, Color.R, Color.G, Color.B);
}

void FRenderer::DrawPointAtRelative(const FColorPoint& ColorPoint) const
{
	SDL_SetRenderDrawColor(Renderer, ColorPoint.Color.R, ColorPoint.Color.G, ColorPoint.Color.B, ColorPoint.Color.A);

	const FVector2D<int> DrawLocation = ConvertLocationToScreenSpace(ColorPoint.Location);

	SDL_RenderDrawPoint(Renderer, DrawLocation.X, DrawLocation.Y);
}

void FRenderer::DrawPointAtAbsolute(const FColorPoint& ColorPoint) const
{
	SDL_SetRenderDrawColor(Renderer, ColorPoint.Color.R, ColorPoint.Color.G, ColorPoint.Color.B, ColorPoint.Color.A);

	SDL_RenderDrawPoint(Renderer, ColorPoint.Location.X, ColorPoint.Location.Y);
}

void FRenderer::DrawPointsAt(const CArray<FVector2D<int>>& Points, const FColorRGBA& AllPointsColor, const bool bIsLocationRelative) const
{
	SDL_SetRenderDrawColor(Renderer, AllPointsColor.R, AllPointsColor.G, AllPointsColor.B, AllPointsColor.A);
	
	const auto AllPointsNum = static_cast<Uint32>(Points.Size());

	if (AllPointsNum == 0)
	{
		return;
	}
	
	std::vector<SDL_Point> PointsArray(AllPointsNum);

	if (bIsLocationRelative)
	{
		for (unsigned int Index = 0; Index < AllPointsNum; Index++)
		{
			const FVector2D<int> DrawLocation = ConvertLocationToScreenSpace(Points[Index]);

			PointsArray[Index] = { DrawLocation.X, DrawLocation.Y };
		}
	}
	else
	{
		for (unsigned int Index = 0; Index < AllPointsNum; Index++)
		{
			PointsArray[Index] = { Points[Index].X, Points[Index].Y };
		}
	}
	
	SDL_RenderDrawPoints(Renderer, PointsArray.data(), static_cast<int>(PointsArray.size()));
}

void FRenderer::DrawPointsAt(const CArray<SDL_Point>& Points, const FColorRGBA& AllPointsColor, const bool bIsLocationRelative) const
{
	SDL_SetRenderDrawColor(Renderer, AllPointsColor.R, AllPointsColor.G, AllPointsColor.B, AllPointsColor.A);

	if (bIsLocationRelative)
	{
		CArray<SDL_Point> NewPoints = Points;
		for (SDL_Point& NewPoint : NewPoints)
		{
			NewPoint.x += RenderOffset.X;
			NewPoint.y += RenderOffset.Y;
		}

		SDL_RenderDrawPoints(Renderer, NewPoints.Vector.data(), static_cast<int>(NewPoints.Size()));
	}
	else
	{
		SDL_RenderDrawPoints(Renderer, Points.Vector.data(), static_cast<int>(Points.Size()));
	}
}

void FRenderer::DrawRectangle(FVector2D<int> RectLocation, const FVector2D<int> RectSize, const FColorRGBA& InColor, const bool bIsLocationRelative) const
{
	SDL_SetRenderDrawColor(Renderer, InColor.R, InColor.G, InColor.B, InColor.A);

	if (bIsLocationRelative)
	{
		RectLocation = ConvertLocationToScreenSpace(RectLocation);
	}
	
	SDL_Rect Rect;
	Rect.x = RectLocation.X;
	Rect.y = RectLocation.Y;
	Rect.w = RectSize.X;
	Rect.h = RectSize.Y;
	
	SDL_RenderFillRect(Renderer, &Rect);
}

void FRenderer::DrawRectangleOutline(FVector2D<int> RectLocation, const FVector2D<int> RectSize, const FColorRGBA& InColor, const bool bIsLocationRelative) const
{
	SDL_SetRenderDrawColor(Renderer, InColor.R, InColor.G, InColor.B, InColor.A);

	if (bIsLocationRelative)
	{
		RectLocation = ConvertLocationToScreenSpace(RectLocation);
	}
	
	SDL_Rect Rect;
	Rect.x = RectLocation.X;
	Rect.y = RectLocation.Y;
	Rect.w = RectSize.X;
	Rect.h = RectSize.Y;
	
	SDL_RenderDrawRect(Renderer, &Rect);
}

void FRenderer::DrawCircle(FVector2D<int> Location, const int Radius, const bool bIsLocationRelative) const
{
	if (bIsLocationRelative)
	{
		Location = ConvertLocationToScreenSpace(Location);
	}

	int nx = Radius - 1;
	int ny = 0;
	int dx = 1;
	int dy = 1;
	int err = dx - (Radius << 1);

	while (nx >= ny)
	{
		SDL_RenderDrawPoint(Renderer, Location.X + nx, Location.Y + ny);
		SDL_RenderDrawPoint(Renderer, Location.X + ny, Location.Y + nx);
		SDL_RenderDrawPoint(Renderer, Location.X - ny, Location.Y + nx);
		SDL_RenderDrawPoint(Renderer, Location.X - nx, Location.Y + ny);
		SDL_RenderDrawPoint(Renderer, Location.X - nx, Location.Y - ny);
		SDL_RenderDrawPoint(Renderer, Location.X - ny, Location.Y - nx);
		SDL_RenderDrawPoint(Renderer, Location.X + ny, Location.Y - nx);
		SDL_RenderDrawPoint(Renderer, Location.X + nx, Location.Y - ny);

		if (err <= 0)
		{
			ny++;
			err += dy;
			dy += 2;
		}

		if (err > 0)
		{
			nx--;
			dx += 2;
			err += dx - (Radius << 1);
		}
	}
}

void FRenderer::DrawLine(FVector2D<int> From, FVector2D<int> To, const bool bIsLocationRelative) const
{
	if (bIsLocationRelative)
	{
		From = ConvertLocationToScreenSpace(From);
		To = ConvertLocationToScreenSpace(To);
	}

	SDL_RenderDrawLine(GetSDLRenderer(), From.X, From.Y, To.X, To.Y);
}

FVector2D<int> FRenderer::ConvertLocationToScreenSpace(const FVector2D<int>& InLocation) const
{
	return (InLocation + RenderOffset);
}

void FRenderer::SetRenderOffset(const FVector2D<int>& NewRenderOffset)
{
	RenderOffset = NewRenderOffset;
}
