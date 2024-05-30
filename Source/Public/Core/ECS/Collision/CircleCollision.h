// Created by Przemys�aw Wiewi�ra 2024

#pragma once

#include "BaseCollision.h"

struct FCircleCollisionData
{
public:
	FCircleCollisionData(const FVector2D<int>& InLocation, const int InCircleRadius)
		: Location(InLocation)
		, CircleRadius(InCircleRadius)
	{
	}


	const FVector2D<int>& GetLocation() const { return Location; }
	int GetRadius() const { return CircleRadius; }

protected:
	FVector2D<int> Location;

	int CircleRadius;
};

/**
 * Basic BoundingCircles collision
 */
class FCircleCollision : public FCollisionBase
{
public:
	FCircleCollision(const FVector2D<int> Location, const int InCircleRadius);

	int GetBaseExtentRadius() override;

	const FCircleCollisionData& GetCircleCollisionData() const;

protected:
	FCircleCollisionData CircleCollisionData;

};
