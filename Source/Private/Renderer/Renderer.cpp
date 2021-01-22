//

#include "CoreEngine.h"
#include "Renderer/Renderer.h"

FColorPoint::FColorPoint()
	: Location(0)
	, Color(0)
{
}

FColorPoint::FColorPoint(const FVector2D<int> InLocation, const FColorRGBA InColor)
	: Location(InLocation)
	, Color(InColor)
{
}

FRenderer::FRenderer(FWindow* InWindow)
	: Window(InWindow)
	, LastWindowSize(0)
{
	Renderer = SDL_CreateRenderer(InWindow->GetSdlWindow(), -1, 0);

	if (Renderer)
	{
		LOG_INFO("Renderer created!");
		
		SDL_SetRenderDrawColor(Renderer, 34, 91, 211, 255);
	}
	else
	{
		LOG_ERROR("Can not create renderer: " << TEXT(SDL_GetError()));
		
		exit(-32);
	}
}

FRenderer::~FRenderer()
{
	SDL_DestroyRenderer(Renderer);
}

void FRenderer::PreRender()
{
	const FVector2D<int> CurrentWindowSize = Window->GetWindowSize();

	if (CurrentWindowSize != LastWindowSize)
	{
		OnWindowSizeChanged();
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
	SDL_SetRenderDrawColor(Renderer, 100, 100, 100, 255); // Background color
	SDL_RenderPresent(Renderer);
}

void FRenderer::OnWindowSizeChanged()
{
	const FVector2D<int> CurrentWindowLocation = Window->GetWindowLocation();
		
	SDL_Rect ViewportSize;
	ViewportSize.w = LastWindowSize.X;
	ViewportSize.h = LastWindowSize.Y;
	ViewportSize.x = CurrentWindowLocation.X;
	ViewportSize.y = CurrentWindowLocation.Y;
}

void FRenderer::DrawPointAt(const FColorPoint& ColorPoint) const
{
	SDL_SetRenderDrawColor(Renderer, ColorPoint.Color.R, ColorPoint.Color.G, ColorPoint.Color.B, ColorPoint.Color.A);
	SDL_RenderDrawPoint(Renderer, ColorPoint.Location.X, ColorPoint.Location.Y);
}

void FRenderer::DrawPointsAt(const CArray<FColorPoint>& ColorPoints) const
{
	for (size_t i = 0; i < ColorPoints.Size(); i++)
	{
		SDL_SetRenderDrawColor(Renderer, ColorPoints[i].Color.R, ColorPoints[i].Color.G, ColorPoints[i].Color.B, ColorPoints[i].Color.A);
		SDL_RenderDrawPoint(Renderer, ColorPoints[i].Location.X, ColorPoints[i].Location.Y);
	}

	// @TODO consider change to https://wiki.libsdl.org/SDL_RenderDrawPoints
}

void FRenderer::DrawPointsAt(const CArray<FVector2D<int>>& Points, FColorRGBA& Color) const
{
	for (size_t i = 0; i < Points.Size(); i++)
	{
		SDL_SetRenderDrawColor(Renderer, Color.R, Color.G, Color.B, Color.A);
		SDL_RenderDrawPoint(Renderer, Points[i].X, Points[i].Y);
	}

	// @TODO change to https://wiki.libsdl.org/SDL_RenderDrawPoints
}

void FRenderer::DrawCircle(const FVector2D<int> Location, const int Radius)
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

void FRenderer::DrawLimitedLine(int x1, int y1, int x2, int y2, int lineLength)
{
	int dx = abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
	int dy = abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2;

	int i = 0;
	while (SDL_RenderDrawPoint(Renderer, x1, y1), i < lineLength)
	{
		int e2 = err;
		if (e2 > -dx) { err -= dy; x1 += sx; }
		if (e2 < dy) { err += dx; y1 += sy; }
		i++;
	}
}
