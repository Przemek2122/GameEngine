// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"

/** Make as def to be able to change in single place in case of need */
typedef FVector2D<int32> FTransformLocation;
typedef int32 FTransformRotation;

enum class ETransformAttachType
{
	/** Default transform method, just attach to parent to follow parent movement. */
	DefaultAttached,

	/** Will be more advanced than DefaultAttached because it will also rotate around parent */
	AttachWithRotateAroundParent
};

/** Structure with location and rotation in 2D */
struct FTransform2D
{
	FTransform2D();

	FTransformLocation Location;
	FTransformRotation Rotation;
};

/**
 * Interface for managing location and rotation
 * Note:
 * Location and rotation are absolute to world (0, 0) if not attached
 * and Location and rotation are relative to parent if attached
 */
class FTransform2DInterface
{
public:
	FTransform2DInterface();
	virtual ~FTransform2DInterface() = default;

	const FTransform2D& GetAbsoluteTransform() const { return AbsoluteTransform2D; }
	const FTransformLocation& GetAbsoluteLocation() const { return AbsoluteTransform2D.Location; }
	FTransformRotation GetAbsoluteRotation() const { return AbsoluteTransform2D.Rotation; }

	const FTransform2D& GetTransform() const { return RelativeTransform2D; }
	const FTransformLocation& GetLocation() const { return RelativeTransform2D.Location; }
	FTransformRotation GetRotation() const { return RelativeTransform2D.Rotation; }

	void SetTransform(const FTransform2D& NewTransform2D);
	void SetLocation(const FTransformLocation& NewLocation);
	void SetRotation(const FTransformRotation NewRotation);

	CArray<FTransform2DInterface*>& GetChildrenInterfaces() { return ChildrenInterfaces; }

	void AddUpdatedComponent(FTransform2DInterface* InTransform2DInterface);
	void RemoveUpdatedComponent(FTransform2DInterface* InTransform2DInterface);

	void OnParentLocationChanged(const FTransformLocation& NewLocation);
	void OnParentRotationChanged(const FTransformRotation NewRotation);

	virtual void OnLocationChanged();
	virtual void OnRotationChanged();

	/** Called when location changed */
	FDelegate<void, const FTransformLocation&> OnLocationChangedDelegate;

	/** Called when rotation is changed */
	FDelegate<void, FTransformRotation> OnRotationChangedDelegate;

private:
	/** Child array of interfaces */
	CArray<FTransform2DInterface*> ChildrenInterfaces;

	/** 2D Location and rotation in world space */
	FTransform2D AbsoluteTransform2D;

	/** 2D Location and rotation got from parent on each parent change */
	FTransform2D ParentTransform2D;

	/** 2D Location and rotation relative to parent, or world (0, 0) for master interface */
	FTransform2D RelativeTransform2D;

};
