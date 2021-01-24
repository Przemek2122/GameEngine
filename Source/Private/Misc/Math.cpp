// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Misc/Math.h"

FVector2D<int> FMath::GetRectCenter(const SDL_Rect Rect)
{
	return FVector2D<int>(Rect.x + (Rect.w / 2), Rect.y + (Rect.h / 2));
}
