// Created by Przemys�aw Wiewi�ra 2020

#pragma once

#include "ECS/Component.h"
#include "Interfaces/TransformInterface2D.h"

/**
 * Component for handling transform of the entity
 */
class UMoveComponent : public UComponent, public ITransformParentInterface2D<int>
{
public:
	UMoveComponent(IComponentManagerInterface* InComponentManagerInterface);
	virtual ~UMoveComponent() override = default;

	

};