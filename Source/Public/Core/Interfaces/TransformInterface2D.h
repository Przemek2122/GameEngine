// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"

template<typename TType>
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


	/** User location */
	FVector2D<TType> GetLocationUser() const
	{
		return UserLocation;
	}

	/** Map location */
	FVector2D<TType> GetLocationMap() const
	{
		return MapLocationOffset;
	}

	/** Final location - User set location + Map location */
	FVector2D<TType> GetLocationFinal() const
	{
		return FinalLocation;
	}


	void SetLocationUser(const FVector2D<TType>& NewLocation)
	{
		UserLocation = NewLocation;

		UpdateFinalLocation();
	}

	void SetLocationMap(const FVector2D<TType>& NewLocation)
	{
		MapLocationOffset = NewLocation;

		UpdateFinalLocation();
	}

	void SetLocationFinal(const FVector2D<TType>& NewLocation)
	{
		FinalLocation = NewLocation;

		UserLocation = FinalLocation - MapLocationOffset;
	}

	
	TType GetRotation() const
	{
		return Rotation;
	}

	void SetRotation(const TType& NewRotation) const
	{
		Rotation = NewRotation;
	}

protected:
	void UpdateFinalLocation()
	{
		FinalLocation = UserLocation + MapLocationOffset;
	}

protected:
	/** Location set by user only. */
	FVector2D<TType> UserLocation;

	/** Location of map offset only. From map (used when map is moved) */
	FVector2D<TType> MapLocationOffset;

	/** Total Location. FinalLocation = Location + MapLocationOffset */
	FVector2D<TType> FinalLocation;

	/** Rotation */
	TType Rotation;

};
