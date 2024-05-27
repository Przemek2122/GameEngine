// Created by Przemys�aw Wiewi�ra 2024

#pragma once

#include "BaseCollision.h"

/**
 * Basic BoundingCircles collision
 */
class FCircleCollision : public FCollisionBase
{
public:
	FCircleCollision(const int InCircleRadius);

	int GetBaseExtentRadius() override;

	int GetCircleRadius() const { return CircleRadius; }

protected:
	int CircleRadius;

};
