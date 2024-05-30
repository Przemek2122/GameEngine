// Created by Przemys³aw Wiewióra 2024

#include "CoreEngine.h"
#include "ECS/Collision/CircleCollision.h"

FCircleCollision::FCircleCollision(const FVector2D<int> InLocation, const int InCircleRadius)
	: CircleCollisionData(InLocation, InCircleRadius)
{
}

int FCircleCollision::GetBaseExtentRadius()
{
	return CircleCollisionData.GetRadius();
}

const FCircleCollisionData& FCircleCollision::GetCircleCollisionData() const
{
	return CircleCollisionData;
}
