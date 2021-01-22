// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"
#include "Vector2D.h"

/* Two dimensional vector. */
class FColorRGBA
{
public:
	FColorRGBA();
	
	/** Initialize R, G, B with In, A(1), ColorRangeMin(0.f), ColorRangeMax(1.f) */
	FColorRGBA(const Uint8 In);

	/** Initialize R, G, B, A(1), ColorRangeMin(0.f), ColorRangeMax(1.f)*/
	FColorRGBA(const Uint8 InR, const Uint8 InG, const Uint8 InB);
	
	/** Initialize R, G, B, A, ColorRangeMin(0.f), ColorRangeMax(1.f) */
	FColorRGBA(const Uint8 InR, const Uint8 InG, const Uint8 InB, const Uint8 InA);

	/** Full initializer */
	FColorRGBA(const Uint8 InR, const Uint8 InG, const Uint8 InB, const Uint8 InA, const Uint8 InColorRangeMin, const Uint8 InColorRangeMax);
	
	/**
	 * Initialize from FVector
	 * R = X, G = Y, B(0), A(1), ColorRangeMin(0.f), ColorRangeMax(1.f)
	 */
	FColorRGBA(FVector2D<int>& OldVector);
	
	/**
	 * Initialize from FVector
	 * R = X, G = Y, B(0), A(1), ColorRangeMin(0.f), ColorRangeMax(1.f)
	 */
	FColorRGBA(FVector2D<float>& OldVector);
	
	/**
	 * Initialize from FVector
	 * R = X, G = Y, B(0), A(1), ColorRangeMin(0.f), ColorRangeMax(1.f)
	 */
	FColorRGBA(FVector2D<double>& OldVector);

	void SetColorRange(const float InColorRangeMin = 0.f, const float InColorRangeMax = 1.f);

	/** Clamps values to be between min and max of 'ColorRange'. */
	void NormalizeValues();

	// Conversion
	operator std::ostream&() const 
	{
		return std::ostringstream().flush() << "(" + std::to_string(R) + ", " + std::to_string(R) + ")";
	}
	operator std::string() const 
	{ 
		return "(" + std::to_string(R) + ", " + std::to_string(R) + ")"; 
	}
	
public:
	Uint8 R;
	Uint8 G;
	Uint8 B;
	Uint8 A;

protected:
	Uint8 ColorRangeMin;
	Uint8 ColorRangeMax;
};
