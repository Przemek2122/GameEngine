// Created by Przemys�aw Wiewi�ra 2024

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
