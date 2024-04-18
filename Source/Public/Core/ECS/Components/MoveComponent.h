// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "ECS/Component.h"
#include "Interfaces/TransformInterface2D.h"

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
class UMoveComponent : public UComponent, public ITransformChildInterface2D<int>
{
public:
	UMoveComponent(IComponentManagerInterface* InComponentManagerInterface);
	virtual ~UMoveComponent() override = default;

	void BeginPlay() override;

	void Tick(const float DeltaTime) override;

	/** Set where unit should go. */
	void SetTargetMoveLocation(const FVector2D<int> NewTargetLocation);

	/** Cancel moving to TargetLocation */
	void AbortMovement();

	/** Teleports user by given distance in given direction */
	void MoveByUnits(const float Distance, const EMovementDirection MovementDirection = EMovementDirection::Forward);

protected:
	/** Location desired by unit. This is the place where we want to move to. */
	FVector2D<int> TargetLocation;

	UBaseTransformComponent* RootTransformComponent;

#if _DEBUG
	UArrowComponent* ArrowComponent = nullptr;
	bool bShowForwardArrow = true;
#endif

};