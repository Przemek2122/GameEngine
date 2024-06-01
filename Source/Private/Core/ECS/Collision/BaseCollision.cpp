// Created by Przemys�aw Wiewi�ra 2024

#include "CoreEngine.h"
#include "ECS/Collision/BaseCollision.h"

FCollisionBase::FCollisionBase()
	: CollisionType(ECollisionType::Other)
{
}

int FCollisionBase::GetBaseExtentRadius()
{
	return 0;
}

ECollisionType FCollisionBase::GetCollisionType() const
{
	return CollisionType;
}
