// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"

template<typename TType>
class ITransformChildInterface2D;

template<typename TType>
class ITransformParentInterface2D;

template<typename TType>
class IBaseTransformInterface2D
{
public:
	virtual ~IBaseTransformInterface2D() = default;

	void AddUpdatedComponent(ITransformChildInterface2D<TType>* UpdatedComponent)
	{
		UpdatedComponents.Push(UpdatedComponent);
	}

	void RemoveUpdatedComponent(ITransformChildInterface2D<TType>* UpdatedComponent)
	{
		UpdatedComponents.Remove(UpdatedComponent);
	}

	void UpdateSubComponentsLocation()
	{
		for (ITransformChildInterface2D<TType>* Component : UpdatedComponents)
		{
			Component->SetParentLocation(GetLocation());
		}
	}

	void UpdateSubComponentsRotation()
	{
		for (ITransformChildInterface2D<TType>* Component : UpdatedComponents)
		{
			Component->SetParentRotation(GetRotation());
		}
	}

	virtual const FVector2D<TType>& GetLocation() const = 0;
	virtual TType GetRotation() const = 0;

protected:
	/** Children */
	CArray<ITransformChildInterface2D<TType>*> UpdatedComponents;
	
};

/**
 * Interface for handling transform of the entity 2d (root component)
 */
template<typename TType>
class ITransformChildInterface2D : public IBaseTransformInterface2D<TType>
{
	friend class ITransformParentInterface2D<TType>;

public:
	ITransformChildInterface2D()
		: ParentRotation(0)
		, RotationRelative(0)
		, RotationAbsolute(0)
	{
	}
	virtual ~ITransformChildInterface2D() = default;

	/** Begin IBaseTransformInterface2D */
	/** @returns absolute location */
	const FVector2D<TType>& GetLocation() const override
	{
		return LocationAbsolute;
	}

	/** @returns absolute rotation */
	TType GetRotation() const override
	{
		return RotationAbsolute;
	}
	/** End IBaseTransformInterface2D */

	/** @returns current location absolute */
	const FVector2D<TType>& GetLocationAbsolute() const
	{
		return LocationAbsolute;
	}

	/** @returns current location relative to parent */
	const FVector2D<TType>& GetLocationRelative() const
	{
		return LocationRelative;
	}

	/** Set absolute location. This functions skips parent offset. */
	void SetLocationAbsolute(const FVector2D<TType>& NewLocation)
	{
		LocationRelative = NewLocation - LocationRelative;

		UpdateLocation();
	}

	/** Set relative location. This funciton will set location to @NewLocation + Parent location */
	void SetLocationRelative(const FVector2D<TType>& NewLocation)
	{
		LocationRelative = NewLocation;

		UpdateLocation();
	}

	/**
	 * Update parent Location. Do not use unless you want to update parent location for some reason.
	 * Use SetLocationAbsolute or SetLocationRelative instead.
	 */
	void SetParentLocation(const FVector2D<TType>& NewLocation)
	{
		ParentLocation = NewLocation;

		UpdateLocation();
	}

	TType GetRotationAbsolute() const
	{
		return RotationAbsolute;
	}

	TType GetRotationRelative() const
	{
		return (RotationRelative);
	}

	/** Local offset from parent rotation */
	void SetRotationAbsolute(const TType& NewRotation)
	{
		RotationRelative = NewRotation - ParentRotation;

		UpdateRotation();
	}

	/** Local offset from parent rotation */
	void SetRotationRelative(const TType& NewRotation)
	{
		RotationRelative = NewRotation;

		UpdateRotation();
	}

	/**
	 * Update parent rotation. Do not use unless you want to update parent rotation for some reason.
	 * Use SetRotationRelative instead.
	 */
	void SetParentRotation(const TType& NewRotation)
	{
		ParentRotation = NewRotation;

		UpdateRotation();
	}

	virtual void OnTransformLocationChanged()
	{
	}

	virtual void OnTransformRotationChanged()
	{
	}

protected:
	void UpdateLocation()
	{
		LocationAbsolute = ParentLocation + LocationRelative;

		OnTransformLocationChanged();

		IBaseTransformInterface2D<TType>::UpdateSubComponentsLocation();
	}

	void UpdateRotation()
	{
		RotationAbsolute = ParentRotation + RotationRelative;

		OnTransformRotationChanged();

		IBaseTransformInterface2D<TType>::UpdateSubComponentsRotation();
	}

private:
	/** Location set by parent. */
	FVector2D<TType> ParentLocation;

	/**  */
	FVector2D<TType> LocationRelative;

	/**  */
	FVector2D<TType> LocationAbsolute;

	/** Rotation of Parent */
	TType ParentRotation;

	/**  */
	TType RotationRelative;

	/**  */
	TType RotationAbsolute;

};

/**
 * Interface for handling transform of the entity 2d (root component)
 */
template<typename TType>
class ITransformParentInterface2D : public IBaseTransformInterface2D<TType>
{
public:
	ITransformParentInterface2D()
		: Rotation(0)
	{
	}

	virtual ~ITransformParentInterface2D() = default;

	/** Returns current location */
	const FVector2D<TType>& GetLocation() const override
	{
		return Location;
	}

	/** Set exact location */
	void SetLocation(const FVector2D<TType>& NewLocation)
	{
		Location = NewLocation;

		UpdateLocation();
	}

	/** Add location to current location - move by @LocationToAdd */
	void AddLocation(const FVector2D<TType> LocationToAdd)
	{
		Location += LocationToAdd;

		UpdateLocation();
	}
	
	TType GetRotation() const override
	{
		return Rotation;
	}

	void SetRotation(const TType& NewRotation)
	{
		Rotation = NewRotation;

		UpdateRotation();
	}

	void AddRotation(const TType& RotationToAdd)
	{
		Rotation += RotationToAdd;

		UpdateRotation();
	}

	virtual void OnTransformLocationChanged()
	{
	}

	virtual void OnTransformRotationChanged()
	{
	}

protected:
	void UpdateLocation()
	{
		OnTransformLocationChanged();

		IBaseTransformInterface2D<TType>::UpdateSubComponentsLocation();
	}

	void UpdateRotation()
	{
		OnTransformRotationChanged();

		IBaseTransformInterface2D<TType>::UpdateSubComponentsRotation();
	}

private:
	/** Location */
	FVector2D<TType> Location;

	/** Rotation */
	TType Rotation;

};
