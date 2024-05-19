// Created by Przemys�aw Wiewi�ra 2020-2024

#pragma once

#include "ECS/BaseComponent.h"

/**
 * Component for handling transform of the entity
 */
class UPhysicsComponent : public UBaseComponent
{
public:
	UPhysicsComponent(IComponentManagerInterface* InComponentManagerInterface);
	virtual ~UPhysicsComponent() override = default;

};
