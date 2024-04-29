// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "ECS/BaseComponent.h"
#include "Interfaces/TransformInterface2D.h"

/**
 * Component for finding target
 */
class UTargetingComponent : public UBaseComponent, public ITransformChildInterface2D<int>
{
public:
	UTargetingComponent(IComponentManagerInterface* InComponentManagerInterface);
	virtual ~UTargetingComponent() override = default;

	

};