// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Misc/Math.h"

FVector2D<int> FMath::GetRectCenter(const SDL_Rect Rect)
{
	return {
		Rect.x + (Rect.w / 2),
		Rect.y + (Rect.h / 2)
	};
}

int FMath::RoundToInt(const float Value)
{
	return static_cast<int>(std::roundf(Value));
}

int FMath::RoundToInt(const double Value)
{
	return static_cast<int>(std::round(Value));
}

int FMath::CeilToInt(const float Value)
{
	return static_cast<int>(std::ceilf(Value));
}

int FMath::CeilToInt(const double Value)
{
	return static_cast<int>(std::ceil(Value));
}

int FMath::FloorToInt(const float Value)
{
	return static_cast<int>(std::floorf(Value));
}

int FMath::FloorToInt(const double Value)
{
	return static_cast<int>(std::floor(Value));
}
