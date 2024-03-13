// Created by Przemys³aw Wiewióra 2020

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