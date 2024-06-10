// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "ECS/Component.h"

class UParentComponent;
class UArrowComponent;

enum class EMovementDirection
{
	Forward,
	Backwards,
	Right,
	Left,
};

enum class EMovementMethod
{
	Default,		
	Linear,			// Movement in one direction
};

/**
 * Component for handling transform of the entity
 */
class UMoveComponent : public UComponent
{
public:
	UMoveComponent(IComponentManagerInterface* InComponentManagerInterface);
	virtual ~UMoveComponent() override = default;

	/** Begin UComponent */
	void BeginPlay() override;
	void Tick(const float DeltaTime) override;
	void Render() override;
	/** End UComponent */

	/** How far owner has to be to stop when approaching TargetLocation */
	void SetStoppingDistance(const float InStopDistance);

	/** Reset stop distance to default auto calculated value */
	void ResetStoppingDistance();

	/** Set where unit should go. */
	void SetTargetMoveLocation(const FVector2D<int> NewTargetLocation);

	/** Cancel moving to TargetLocation */
	void AbortMovement();

	void SetShouldRotateInstant(const bool bInShouldRotateInstant);

	bool IsMoving() const;

	virtual void SetMovementMethod(EMovementMethod NewMovementMethod);

	void SetLinearSpeedPerSecond(const float NewSpeed);
	void SetAngularSpeedPerSecond(const float NewSpeed);

protected:
	/** Teleports owner by given distance in given direction */
	void MoveByUnits(const float Distance, const EMovementDirection MovementDirection = EMovementDirection::Forward);

	void UpdateRotationToTarget(float DeltaTime);
	void UpdateLocationToTarget(float DeltaTime);

	void UpdateLocationLinear(float DeltaTime);

	virtual void OnRequestedLocationOutOfBounds();

protected:
	/** Location desired by unit. This is the place where we want to move to. */
	FVector2D<int> TargetLocation;

	/** If true, component owner is moving */
	bool bHasTargetMoveToLocation;

	/** if true we will not make smooth rotation but instant rotation */
	bool bShouldRotateInstant;

	/** Distance to stop when moving */
	float StopDistance;

	float LinearSpeedPerSecond;
	float AngularSpeedPerSecond;

	FVector2D<float> PreciseLocation;
	float PreciseRotation;

	UParentComponent* RootTransformComponent;

	FVector2D<int> CurrentLocation;
	FVector2D<int> CalculatedTargetLocation;

	bool bHasCustomStopDistance;

#if _DEBUG
	UArrowComponent* ArrowComponent = nullptr;
	bool bShowForwardArrow = true;
#endif

private:
	EMovementMethod CurrentMovementMethod;

};