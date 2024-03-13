// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "ECS/Component.h"

UComponent::UComponent(IComponentManagerInterface* InComponentManagerInterface)
	: IComponentManagerInterface(InComponentManagerInterface)
{
}

UComponent::~UComponent()
{
}

void UComponent::BeginPlay()
{
}

void UComponent::EndPlay()
{
}

void UComponent::Tick()
{
}

void UComponent::Render()
{
}
