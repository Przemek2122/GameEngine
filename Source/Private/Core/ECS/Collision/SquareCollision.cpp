// Created by Przemys³aw Wiewióra 2024

#include "CoreEngine.h"
#include "ECS/Collision/SquareCollision.h"

void FSquareData::UpdateDiagonalSize()
{
	DiagonalSize = FMath::Sqrt(FMath::Power(Size.X) + FMath::Power(Size.Y));
}

const FVector2D<int>& FSquareData::GetLocation() const
{
	return Location;
}

const FVector2D<int>& FSquareData::GetSize() const
{
	return Size;
}

int FSquareData::GetDiagonalSize() const
{
	return DiagonalSize;
}

void FSquareData::UpdateLocation(const FVector2D<int>& InLocation)
{
	Location = InLocation;
}

void FSquareData::UpdateSize(const FVector2D<int>& InSize)
{
	Size = InSize;

	UpdateDiagonalSize();
}

FSquareCollision::FSquareCollision(const FVector2D<int> InLocation, const FVector2D<int> InSize)
	: SquareData(InLocation, InSize)
{
}

int FSquareCollision::GetBaseExtentRadius()
{
	return (SquareData.GetDiagonalSize() / 2);
}

const FSquareData& FSquareCollision::GetSquareData() const
{
	return SquareData;
}

FSquareData& FSquareCollision::GetSquareDataForEdit()
{
	return SquareData;
}

int FSquareCollision::GetDiagonalSize() const
{
	return SquareData.GetDiagonalSize();
}
