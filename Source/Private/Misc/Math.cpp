// Created by Przemys�aw Wiewi�ra 2020

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

float FMath::RandRange(const float Min, const float Max)
{
	const float RawRandomFloat = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	const float MinMaxDiff = Max - Min;
	const float Result = RawRandomFloat * MinMaxDiff;

	return Min + Result;
}

int FMath::RandRange(const int Min, const int Max)
{
	const int RawRandomInt = rand(); // Generates a random integer 
	const int MinMaxDiff = Max - Min;
	const int Result = RawRandomInt % (MinMaxDiff + 1); // Use modulo to constrain range 

	return Min + Result;
}

float FMath::RadiansToDegrees(float Value)
{
	return static_cast<float>(Value * 180 / M_PI);
}

double FMath::RadiansToDegreesDouble(double Value)
{
	return Value * 180 / M_PI;
}

float FMath::DegreesToRadians(float Value)
{
	return static_cast<float>(2 * M_PI * (Value / 360));
}

double FMath::DegreesToRadiansDouble(double Value)
{
	return (2 * M_PI * (Value / 360));
}

double FMath::Get2DAngleOfPointRadians(const FVector2D<> A, const FVector2D<> B)
{
	return atan2(A.Y - B.Y, A.X - B.X);
}

void FMath::RotatePointAroundPoint(const FVector2D<int>& Pivot, const float& Angle, FVector2D<int>& Point)
{
	const float Sinus = sin(Angle);
	const float Cosinus = cos(Angle);

	// translate point back to origin:
	Point.X -= Pivot.X;
	Point.Y -= Pivot.Y;

	// rotate point
	const float NewX = static_cast<float>(Point.X) * Cosinus - static_cast<float>(Point.Y) * Sinus;
	const float NewY = static_cast<float>(Point.X) * Sinus + static_cast<float>(Point.Y) * Cosinus;

	// translate point back:
	Point.X = RoundToInt(NewX + static_cast<float>(Pivot.X));
	Point.Y = RoundToInt(NewY + static_cast<float>(Pivot.Y));
}

int FMath::FloorToInt(const float Value)
{
	return static_cast<int>(std::floorf(Value));
}

int FMath::FloorToInt(const double Value)
{
	return static_cast<int>(std::floor(Value));
}
