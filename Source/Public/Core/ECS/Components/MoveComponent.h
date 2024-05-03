// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "ECS/Component.h"

class UBaseTransformComponent;

enum class EMovementDirection
{
	Forward,
	Backwards,
	Right,
	Left,
};

class UArrowComponent;

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

	/** Set where unit should go. */
	void SetTargetMoveLocation(const FVector2D<int> NewTargetLocation);

	/** Cancel moving to TargetLocation */
	void AbortMovement();

	bool IsMoving() const;

protected:
	/** Teleports owner by given distance in given direction */
	void MoveByUnits(const float Distance, const EMovementDirection MovementDirection = EMovementDirection::Forward);

	void UpdateRotation(float DeltaTime);
	void UpdateLocation(float DeltaTime);

protected:
	/** Location desired by unit. This is the place where we want to move to. */
	FVector2D<int> TargetLocation;

	/** If true, component owner is moving */
	bool bHasTargetMoveToLocation;

	/** Distance to stop when moving */
	float StopDistance;

	float LinearSpeedPerSecond;
	float AngularSpeedPerSecond;

	FVector2D<float> PreciseLocation;
	float PreciseRotation;

	UBaseTransformComponent* RootTransformComponent;

	FVector2D<int> CurrentLocation;
	FVector2D<int> CalculatedTargetLocation;

#if _DEBUG
	UArrowComponent* ArrowComponent = nullptr;
	bool bShowForwardArrow = true;
#endif

};