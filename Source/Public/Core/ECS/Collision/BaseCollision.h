// Created by Przemys³aw Wiewióra 2024

#pragma once

class FCollisionBase
{
public:
	virtual ~FCollisionBase() = default;

	/** @returns radius for basic distance check. */
	virtual int GetBaseExtentRadius();
	
};
