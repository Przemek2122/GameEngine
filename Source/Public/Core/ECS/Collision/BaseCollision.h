// Created by Przemys�aw Wiewi�ra 2024

#pragma once

enum class ECollisionType
{
	Circle,
	Square,
	Other
};

class FCollisionBase
{
public:
	FCollisionBase();
	virtual ~FCollisionBase() = default;

	/** @returns radius for basic distance check. */
	virtual int GetBaseExtentRadius();

	ECollisionType GetCollisionType() const;

protected:
	ECollisionType CollisionType;

};
