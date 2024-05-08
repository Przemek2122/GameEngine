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
		// Calculate the direction vector from A to B 
		FVector2D<TType> Direction = LookAtTarget - From;

		// Normalize the direction vector 
		FVector2D<float> NormalizedDirection = Direction.Normalize();

		// Calculate the angle in radians 
		float AngleRadians = std::atan2(NormalizedDirection.Y, NormalizedDirection.X);

		return AngleRadians;
	}

	/** @Returns radians angle to look at LookAtTarget. Performs automatic conversion to degrees */
	template <typename TType>
	static float FindLookAtRotationInDegrees(const FVector2D<TType> From, const FVector2D<TType> LookAtTarget)
	{
		// @TODO HACK
		static constexpr float RotationOffset = 90.f;

		return FMath::ClampAngle(RadiansToDegrees(FindLookAtRotationInRadians(From, LookAtTarget)) + RotationOffset);
	}

	template<typename TType>
	static int Clamp(const TType Value, const TType Min,  const TType Max)
	{
		if (Value < Min)
		{
			return Min;
		}
		else if (Value > Max)
		{
			return Max;
		}
		else
		{
			return Value;
		}
	}

	template<typename TType>
	static float ClampAngle(const TType Value)
	{
		static constexpr float AngleMin = 0.f;
		static constexpr float AngleMax = 360.f;

		float FinalValue = Value;

		if (FinalValue < AngleMin)
		{
			FinalValue += AngleMax;
		}
		else if (FinalValue > AngleMax)
		{
			FinalValue -= AngleMax;
		}

		return FinalValue;
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

	template<typename TType = float>
	static bool IsNearlyEqual(TType A, TType B, float Tolerance = 0.0001f)
	{
		return (Abs(A - B) < Tolerance);
	}

};
