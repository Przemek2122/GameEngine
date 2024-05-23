// Created by Przemys³aw Wiewióra 2024

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
