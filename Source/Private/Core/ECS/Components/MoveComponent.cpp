// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "ECS/Components/MoveComponent.h"
#include "ECS/Components/ArrowComponent.h"
#include "ECS/Components/BaseTransformComponent.h"

UMoveComponent::UMoveComponent(IComponentManagerInterface* InComponentManagerInterface)
	: UComponent(InComponentManagerInterface)
{
#if _DEBUG
	if (bShowForwardArrow)
	{
		ArrowComponent = CreateComponent<UArrowComponent>("ForwardArrowComponent");
	}
#endif
}

void UMoveComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UMoveComponent::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void UMoveComponent::SetTargetMoveLocation(const FVector2D<int> NewTargetLocation)
{
	TargetLocation = NewTargetLocation;
}

void UMoveComponent::AbortMovement()
{
	TargetLocation = FVector2D<int>();
}

void UMoveComponent::MoveByUnits(const float Distance, const EMovementDirection MovementDirection)
{
}
