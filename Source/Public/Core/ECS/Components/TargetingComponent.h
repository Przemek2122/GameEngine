// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "ECS/Component.h"
#include "Interfaces/TransformInterface2D.h"

/**
 * Component for finding target
 */
class UTargetingComponent : public UComponent, public ITransformChildInterface2D<int>
{
public:
	UTargetingComponent(IComponentManagerInterface* InComponentManagerInterface);
	virtual ~UTargetingComponent() override = default;

	

};