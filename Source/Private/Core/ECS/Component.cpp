// Created by Przemys�aw Wiewi�ra 2020

#include "CoreEngine.h"
#include "ECS/Component.h"

UComponent::UComponent(IComponentManagerInterface* InComponentManagerInterface)
	: ComponentManagerInterface(InComponentManagerInterface)
{
}

UComponent::~UComponent()
{
}
