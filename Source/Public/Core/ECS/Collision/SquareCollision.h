// Created by Przemys³aw Wiewióra 2024

#pragma once

#include "BaseCollision.h"

struct FSquareData
{
public:
	FSquareData(const FVector2D<int>& InLocation, const FVector2D<int>& InSize)
		: Location(InLocation)
		, Size(InSize)
	{
		UpdateDiagonalSize();
	}

	void UpdateDiagonalSize();

	/** Location of left top corner */
	FVector2D<int> GetLocation() const;

	/** Size in width and height */
	FVector2D<int> GetSize() const;

	/** Calculated diagonal of square */
	int GetDiagonalSize() const;

protected:
	/** Location of left top corner */
	FVector2D<int> Location;

	/** Size in width and height */
	FVector2D<int> Size;

	/** Calculated diagonal of square  */
	int DiagonalSize;
};

/**
 * Basic AABB Collision
 */
class FSquareCollision : public FCollisionBase
{
public:
	FSquareCollision(const FVector2D<int> InLocation, const FVector2D<int> InSize);

	int GetBaseExtentRadius() override;

	const FSquareData& GetSquareData() const;

	int GetDiagonalSize() const;

protected:
	FSquareData SquareData;

};
