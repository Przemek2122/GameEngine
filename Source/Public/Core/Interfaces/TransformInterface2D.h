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
class ITransformChildInterface2D;

template<typename TType>
class ITransformInterface2D
{
public:
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
			Component->SetLocationFromParent(GetLocation());
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
class ITransformChildInterface2D : public ITransformInterface2D<TType>
{
public:
	ITransformChildInterface2D()
	{
	}
	virtual ~ITransformChildInterface2D() = default;

	/** User location */
	const FVector2D<TType>& GetLocation() const override
	{
		return FinalLocation;
	}

	void SetLocationFromParent(const FVector2D<TType>& NewLocation)
	{
		ParentLocation = NewLocation;

		UpdateLocation();
	}

	void SetLocationOffset(const FVector2D<TType>& NewLocation)
	{
		ParentLocationOffset = NewLocation;

		UpdateLocation();
	}

	TType GetRotation() const override
	{
		return FinalRotation;
	}

	TType GetRotationOffsetFromParent() const
	{
		return ParentRotationOffset;
	}

	/** Update parent rotation, do not use unless you want to update parent rotation for some reason. Use SetRotationOffset instead */
	void SetParentRotation(const TType& NewRotation) const
	{
		ParentRotation = NewRotation;

		UpdateRotation();
	}

	/** Local offset from parent rotation */
	void SetRotationOffset(const TType& NewRotation) const
	{
		ParentRotationOffset = NewRotation;

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
		FinalLocation = ParentLocation + ParentLocationOffset;

		OnTransformLocationChanged();

		ITransformInterface2D<TType>::UpdateSubComponentsLocation();
	}

	void UpdateRotation()
	{
		FinalRotation = ParentRotation + ParentRotationOffset;

		OnTransformRotationChanged();

		ITransformInterface2D<TType>::UpdateSubComponentsRotation();
	}

protected:
	/** Location set by parent. */
	FVector2D<TType> ParentLocation;

	/** Location offset from parent - final location */
	FVector2D<TType> ParentLocationOffset;

	FVector2D<TType> FinalLocation;

	/** Rotation of Parent */
	TType ParentRotation;

	/** Rotation offset of Parent - final rotation */
	TType ParentRotationOffset;

	TType FinalRotation;

};

/**
 * Interface for handling transform of the entity 2d (root component)
 */
template<typename TType>
class ITransformParentInterface2D : public ITransformInterface2D<TType>
{
public:
	ITransformParentInterface2D()
	{
	}
	virtual ~ITransformParentInterface2D() = default;

	/** Final location - User set location + Map location */
	const FVector2D<TType>& GetLocation() const override
	{
		return FinalLocation;
	}

	/** User location */
	const FVector2D<TType>& GetLocationUser() const
	{
		return UserLocation;
	}

	/** Map location */
	const FVector2D<TType>& GetLocationMap() const
	{
		return MapLocationOffset;
	}

	void SetLocationUser(const FVector2D<TType>& NewLocation)
	{
		UserLocation = NewLocation;

		UpdateLocationAfterMapOrUserChange(ELocationChangeType::LCT_User);
	}

	void SetLocationMap(const FVector2D<TType>& NewLocation)
	{
		MapLocationOffset = NewLocation;

		UpdateLocationAfterMapOrUserChange(ELocationChangeType::LCT_Map);
	}

	void SetLocationFinal(const FVector2D<TType>& NewLocation)
	{
		FinalLocation = NewLocation;

		UpdateLocationAfterDirectChange();
	}
	
	TType GetRotation() const override
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
	void UpdateLocationAfterMapOrUserChange(const ELocationChangeType LocationChangeType)
	{
		FinalLocation = UserLocation + MapLocationOffset;

		OnTransformLocationChanged(LocationChangeType);

		ITransformInterface2D<TType>::UpdateSubComponentsLocation();
	}

	void UpdateLocationAfterDirectChange()
	{
		UserLocation = FinalLocation - MapLocationOffset;

		OnTransformLocationChanged(ELocationChangeType::LCT_User);

		ITransformInterface2D<TType>::UpdateSubComponentsLocation();
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
