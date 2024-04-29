// Created by Przemys³aw Wiewióra 2020

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

	static float GetRandomFloat(float A, float B);

	static float RadiansToDegrees(float Value);
	static double RadiansToDegreesDouble(double Value);

	static float DegreesToRadians(float Value);
	static double DegreesToRadiansDouble(double Value);

	/* Returns radians */
	static double Get2DAngleOfPointRadians(FVector2D<> A, FVector2D<> B);

	/* Expects radians not degree */
	static void RotatePointAroundPoint(const FVector2D<int>& Pivot, const float& Angle, FVector2D<int>& Point);

	/** @Returns radians angle to look at @To */
	template <typename TType>
	static float FindLookAtRotationInRadians(const FVector2D<TType>& From, const FVector2D<TType>& LookAtTarget)
	{
		// Calculate the difference between the two vectors 
		float DiffX = LookAtTarget.x - From.x;
		float DiffY = LookAtTarget.y - From.y;

		// Calculate the angle using atan2 
		const float Angle = atan2(DiffY, DiffX);

		return Angle;
	}

	/** @Returns radians angle to look at LookAtTarget. Performs automatic conversion to degrees */
	template <typename TType>
	static float FindLookAtRotationInDegrees(const FVector2D<TType> From, const FVector2D<TType> LookAtTarget)
	{
		return RadiansToDegrees(FindLookAtRotationInRadians(From, LookAtTarget));
	}

	/** @returns bigger value of two given */
	template<typename TType>
	static int Max(const TType A, const TType B)
	{
		return (A > B) ? A : B;
	}

	/** @returns absolute value (non negative) */
	template<typename TType>
	static TType Abs(const TType Value)
	{
		return (Value < 0) ? -Value : Value;
	}

	/** Square root */
	template<typename TType>
	static TType Sqrt(const TType Value)
	{
		return (sqrt(Value));
	}

	/** Returns power of given value */
	template<typename TType>
	static TType Power(const TType Value)
	{
		return (Value * Value);
	}



};
