// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"

enum class ELocationChangeType
{
	/** Location changed by user */
	LCT_User,

	/** Location changed by map */
	LCT_Map
};

template<typename TType>
class ITransformInterface2D
{
public:
	ITransformInterface2D()
		: Rotation(0)
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

		UpdateFinalLocation(ELocationChangeType::LCT_User);
	}

	void SetLocationMap(const FVector2D<TType>& NewLocation)
	{
		MapLocationOffset = NewLocation;

		UpdateFinalLocation(ELocationChangeType::LCT_Map);
	}

	void SetLocationFinal(const FVector2D<TType>& NewLocation)
	{
		FinalLocation = NewLocation;

		UpdateFinalLocationItself();
	}

	
	TType GetRotation() const
	{
		return Rotation;
	}

	void SetRotation(const TType& NewRotation) const
	{
		Rotation = NewRotation;

		OnTransformRotationChanged();
	}

	virtual void OnTransformLocationChanged(const ELocationChangeType LocationChangeType)
	{
	}

	virtual void OnTransformRotationChanged()
	{
	}

protected:
	void UpdateFinalLocation(const ELocationChangeType LocationChangeType)
	{
		FinalLocation = UserLocation + MapLocationOffset;

		OnTransformLocationChanged(LocationChangeType);
	}

	void UpdateFinalLocationItself()
	{
		UserLocation = FinalLocation - MapLocationOffset;

		OnTransformLocationChanged(ELocationChangeType::LCT_User);
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
