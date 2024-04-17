// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "ECS/Components/MoveComponent.h"

UMoveComponent::UMoveComponent(IComponentManagerInterface* InComponentManagerInterface)
	: UComponent(InComponentManagerInterface)
{
}

void UMoveComponent::Tick(const float DeltaTime)
{
	
}

void UMoveComponent::SetTargetMoveLocation(const FVector2D<int> NewTargetLocation)
{
	TargetLocation = NewTargetLocation;
}
