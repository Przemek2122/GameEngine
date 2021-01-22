// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "ColorRGBA.h"

FColorRGBA::FColorRGBA()
	: R(0.f)
	, G(0.f)
	, B(0.f)
	, A(255)
	, ColorRangeMin(0)
	, ColorRangeMax(255)
{
}

FColorRGBA::FColorRGBA(const Uint8 In)
	: R(In)
	, G(In)
	, B(In)
	, A(255)
	, ColorRangeMin(0)
	, ColorRangeMax(255)
{
}

FColorRGBA::FColorRGBA(const Uint8 InR, const Uint8 InG, const Uint8 InB)
	: R(InR)
	, G(InG)
	, B(InB)
	, A(255)
	, ColorRangeMin(0)
	, ColorRangeMax(255)
{
}

FColorRGBA::FColorRGBA(const Uint8 InR, const Uint8 InG, const Uint8 InB, const Uint8 InA)
	: R(InR)
	, G(InG)
	, B(InB)
	, A(InA)
	, ColorRangeMin(0)
	, ColorRangeMax(255)
{

}

FColorRGBA::FColorRGBA(const Uint8 InR, const Uint8 InG, const Uint8 InB, const Uint8 InA, const Uint8 InColorRangeMin, const Uint8 InColorRangeMax) 
	: R(InR)
	, G(InG)
	, B(InB)
	, A(InA)
	, ColorRangeMin(InColorRangeMin)
	, ColorRangeMax(InColorRangeMax)
{
}

FColorRGBA::FColorRGBA(FVector2D<int>& OldVector)
	: R(OldVector.X)
	, G(OldVector.Y)
	, B(0.f)
	, A(0.f)
	, ColorRangeMin(0.f)
	, ColorRangeMax(1.f)
{
}

FColorRGBA::FColorRGBA(FVector2D<float>& OldVector)
	: R(OldVector.X)
	, G(OldVector.Y)
	, B(0.f)
	, A(0.f)
	, ColorRangeMin(0.f)
	, ColorRangeMax(1.f)
{ 
}

FColorRGBA::FColorRGBA(FVector2D<double>& OldVector)
	: R(static_cast<float>(OldVector.X))
	, G(static_cast<float>(OldVector.Y))
	, B(0.f)
	, A(0.f)
	, ColorRangeMin(0.f)
	, ColorRangeMax(1.f)
{ 
}

void FColorRGBA::SetColorRange(const float InColorRangeMin, const float InColorRangeMax)
{
	ColorRangeMin = InColorRangeMin;
	ColorRangeMax = InColorRangeMax;
}

void FColorRGBA::NormalizeValues()
{
	R = std::clamp(R, ColorRangeMin, ColorRangeMax);
	G = std::clamp(G, ColorRangeMin, ColorRangeMax);
	B = std::clamp(B, ColorRangeMin, ColorRangeMax);
	A = std::clamp(A, ColorRangeMin, ColorRangeMax);
}
