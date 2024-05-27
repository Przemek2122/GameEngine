// Created by Przemys³aw Wiewióra 2024

#include "CoreEngine.h"
#include "ECS/Components/CollisionComponent.h"


UCollisionComponent::UCollisionComponent(IComponentManagerInterface* InComponentManagerInterface)
	: UBaseComponent(InComponentManagerInterface)
{
}
