// Created by Przemys�aw Wiewi�ra 2020

#pragma once

#include "CoreMinimal.h"

/**
 * Static math
 */
class FMath
{
public:
	template<typename TValue = float>
	static float Distance2D(FVector2D<TValue> VectorA, FVector2D<TValue> VectorB)
	{
		// Just a^2 + b^2 = c^2
		const int DistanceX = (VectorB.X - VectorA.X) * (VectorB.X - VectorA.X);
		const int DistanceY = (VectorB.Y - VectorA.Y) * (VectorB.Y - VectorA.Y);

		// Then just square root
		return static_cast<float>(sqrt(DistanceX + DistanceY));
	}
	
	static FVector2D<int> GetRectCenter(const SDL_Rect Rect);

	static int FloorToInt(const float Value);
	static int FloorToInt(const double Value);

	static int RoundToInt(const float Value);
	static int RoundToInt(const double Value);

	static int CeilToInt(const float Value);
	static int CeilToInt(const double Value);

	static int Max(const int A, const int B);

};
