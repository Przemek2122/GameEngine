// Created by Przemys³aw Wiewióra 2020-2024

#pragma once

#include "ECS/Component.h"

/**
 * Component for handling transform of the entity
 */
class UHealthComponent : public UComponent
{
public:
	UHealthComponent(IComponentManagerInterface* InComponentManagerInterface);
	virtual ~UHealthComponent() override = default;

};
