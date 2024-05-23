// Created by Przemys�aw Wiewi�ra 2024

#pragma once

/**
 * Basic BoundingCircles collision
 */
class FCircleCollision
{
public:
	FCircleCollision(const int InCircleRadius);

	int GetCircleRadius() const { return CircleRadius; }

protected:
	int CircleRadius;

};
