// Created by Przemys³aw Wiewióra 2024

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
