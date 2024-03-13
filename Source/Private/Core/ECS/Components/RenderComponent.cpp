// Created by Przemys�aw Wiewi�ra 2020

#include "CoreEngine.h"
#include "ECS/Components/RenderComponent.h"
#include "ECS/Components/TransformComponent.h"

URenderComponent::URenderComponent(IComponentManagerInterface* InComponentManagerInterface)
	: UComponent(InComponentManagerInterface)
{
	RequireComponent<UTransformComponent>();
}
