// Created by Przemys�aw Wiewi�ra 2024

#pragma once

class FCollisionBase
{
public:
	virtual ~FCollisionBase() = default;

	/** @returns radius for basic distance check. */
	virtual int GetBaseExtentRadius();
	
};
