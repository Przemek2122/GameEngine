// See https://github.com/Przemek2122/GameEngine

#include "CoreEngine.h"
#include "Renderer/Renderer.h"

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
	, Renderer(SDL_CreateRenderer(InWindow->GetSdlWindow(), -1, 0))
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

void FRenderer::DrawPointAt(const FColorPoint& ColorPoint) const
{
	SDL_SetRenderDrawColor(Renderer, ColorPoint.Color.R, ColorPoint.Color.G, ColorPoint.Color.B, ColorPoint.Color.A);
	SDL_RenderDrawPoint(Renderer, ColorPoint.Location.X, ColorPoint.Location.Y);
}

void FRenderer::DrawPointsAt(const CArray<FVector2D<int>>& Points, const FColorRGBA& AllPointsColor) const
{
	SDL_SetRenderDrawColor(Renderer, AllPointsColor.R, AllPointsColor.G, AllPointsColor.B, AllPointsColor.A);
	
	const auto AllPointsNum = static_cast<Uint32>(Points.Size());

	if (AllPointsNum == 0)
	{
		return;
	}
	
	std::vector<SDL_Point> PointsArray(AllPointsNum);

	for (unsigned int Index = 0; Index < AllPointsNum; Index++)
	{
		PointsArray[Index] = { Points[Index].X, Points[Index].Y };
	}
	
	SDL_RenderDrawPoints(Renderer, PointsArray.data(), static_cast<int>(PointsArray.size()));
}

void FRenderer::DrawPointsAt(const CArray<SDL_Point>& Points, const FColorRGBA& AllPointsColor) const
{
	SDL_SetRenderDrawColor(Renderer, AllPointsColor.R, AllPointsColor.G, AllPointsColor.B, AllPointsColor.A);
	SDL_RenderDrawPoints(Renderer, Points.Vector.data(), static_cast<int>(Points.Size()));
}

void FRenderer::DrawRectangle(const FVector2D<int> RectLocation, const FVector2D<int> RectSize, const FColorRGBA& InColor) const
{
	SDL_SetRenderDrawColor(Renderer, InColor.R, InColor.G, InColor.B, InColor.A);
	
	SDL_Rect Rect;
	Rect.x = RectLocation.X;
	Rect.y = RectLocation.Y;
	Rect.w = RectSize.X;
	Rect.h = RectSize.Y;
	
	SDL_RenderFillRect(Renderer, &Rect);
}

void FRenderer::DrawRectangleOutline(const FVector2D<int> RectLocation, const FVector2D<int> RectSize, const FColorRGBA& InColor) const
{
	SDL_SetRenderDrawColor(Renderer, InColor.R, InColor.G, InColor.B, InColor.A);
	
	SDL_Rect Rect;
	Rect.x = RectLocation.X;
	Rect.y = RectLocation.Y;
	Rect.w = RectSize.X;
	Rect.h = RectSize.Y;
	
	SDL_RenderDrawRect(Renderer, &Rect);
}

void FRenderer::DrawCircle(const FVector2D<int> Location, const int Radius) const
{
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

void FRenderer::DrawLimitedLine(int X1, int Y1, const int X2, const int Y2, const int LineLength) const
{
	int dx = abs(X2 - X1), sx = X1 < X2 ? 1 : -1;
	int dy = abs(Y2 - Y1), sy = Y1 < Y2 ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2;

	int i = 0;
	while (SDL_RenderDrawPoint(Renderer, X1, Y1), i < LineLength)
	{
		int e2 = err;
		if (e2 > -dx) { err -= dy; X1 += sx; }
		if (e2 < dy) { err += dx; Y1 += sy; }
		i++;
	}
}
