// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "ECS/Components/MoveComponent.h"
#include "ECS/Components/ArrowComponent.h"
#include "ECS/Components/BaseTransformComponent.h"

UMoveComponent::UMoveComponent(IComponentManagerInterface* InComponentManagerInterface)
	: UComponent(InComponentManagerInterface)
	, bHasTargetMoveToLocation(false)
	, StopDistance()
	, MovemenetSpeedPerSecond(10.f)
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

	RootTransformComponent = dynamic_cast<UBaseTransformComponent*>(GetRootComponentOfEntity());
}

void UMoveComponent::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bHasTargetMoveToLocation && RootTransformComponent != nullptr)
	{
		FVector2D<int> CurrentLocation = RootTransformComponent->GetLocation();
		const float CurrentDistance = CurrentLocation.DistanceTo(TargetLocation);

		if (CurrentDistance < StopDistance)
		{
			// We are close enough. Stop.
			AbortMovement();
		}
		else
		{
			// Move to TargetLocation
			MoveByUnits(MovemenetSpeedPerSecond * DeltaTime);
		}
	}
}

void UMoveComponent::SetStoppingDistance(const float InStopDistance)
{
	StopDistance = InStopDistance;
}

void UMoveComponent::SetTargetMoveLocation(const FVector2D<int> NewTargetLocation)
{
	PreciseLocation = RootTransformComponent->GetLocationUser();

	TargetLocation = NewTargetLocation;

	bHasTargetMoveToLocation = true;
}

void UMoveComponent::AbortMovement()
{
	TargetLocation = FVector2D<int>();

	bHasTargetMoveToLocation = false;
}

bool UMoveComponent::IsMoving() const
{
	return bHasTargetMoveToLocation;
}

void UMoveComponent::MoveByUnits(const float Distance, const EMovementDirection MovementDirection)
{
	if (RootTransformComponent != nullptr)
	{
		FVector2D<float> CurrentVector;

		switch (MovementDirection)
		{
			case EMovementDirection::Forward:
			{
				CurrentVector = RootTransformComponent->GetForwardVector();

				break;
			}
			case EMovementDirection::Backwards:
			{
				CurrentVector = -RootTransformComponent->GetForwardVector();

				break;
			}
			case EMovementDirection::Right:
			{


				break;
			}
			case EMovementDirection::Left:
			{


				break;
			}
		}

		const FVector2D<float> LocationToMove = CurrentVector * Distance;
		PreciseLocation += LocationToMove;

		RootTransformComponent->SetLocationUser(LocationToMove);
	}
}
