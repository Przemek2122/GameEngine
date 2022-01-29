// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"

template<typename TType = int>
class ITransformInterface2D
{
public:
	ITransformInterface2D()
		: Rotation(0)
	{
		
	}
	virtual ~ITransformInterface2D()
	{
	}
	
	FVector2D<TType> GetLocation() const
	{
		return Location;
	}
	const FVector2D<TType>& GetLocation() const
	{
		return Location;
	}
	void SetLocation(const FVector2D<TType>& NewLocation)
	{
		Location = NewLocation;
	}
	
	TType GetRotation() const
	{
		return Rotation;
	}
	const TType& GetRotation() const
	{
		return Rotation;
	}
	void SetRotation(const TType& NewRotation) const
	{
		Rotation = NewRotation;
	}

protected:
	FVector2D<TType> Location;
	TType Rotation;

};
