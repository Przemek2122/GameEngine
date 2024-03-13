// Created by Przemys�aw Wiewi�ra 2020

#pragma once

#include "ECS/Component.h"
#include "Interfaces/TransformInterface2D.h"

/**
 * Component for handling transform of the entity
 */
class UTransformComponent : public UComponent, public ITransformInterface2D<int>
{
public:
	UTransformComponent(IComponentManagerInterface* InComponentManagerInterface);
	virtual ~UTransformComponent() override = default;

};