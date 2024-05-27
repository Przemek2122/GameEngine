// Created by Przemys³aw Wiewióra 2024

#include "CoreEngine.h"
#include "ECS/Collision/CircleCollision.h"

FCircleCollision::FCircleCollision(const int InCircleRadius)
	: CircleRadius(InCircleRadius)
{
}

int FCircleCollision::GetBaseExtentRadius()
{
	return GetCircleRadius();
}
