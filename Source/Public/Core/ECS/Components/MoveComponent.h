// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "ECS/Component.h"
#include "Interfaces/TransformInterface2D.h"

/**
 * Component for handling transform of the entity
 */
class UMoveComponent : public UComponent, public ITransformChildInterface2D<int>
{
public:
	UMoveComponent(IComponentManagerInterface* InComponentManagerInterface);
	virtual ~UMoveComponent() override = default;

	void Tick(const float DeltaTime) override;

	/** Set where unit should go. */
	void SetTargetMoveLocation(const FVector2D<int> NewTargetLocation);

protected:
	FVector2D<int> TargetLocation;

};