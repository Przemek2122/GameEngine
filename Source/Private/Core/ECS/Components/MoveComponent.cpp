// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "ECS/Components/MoveComponent.h"
#include "ECS/Components/ArrowComponent.h"
#include "ECS/Components/BaseTransformComponent.h"

UMoveComponent::UMoveComponent(IComponentManagerInterface* InComponentManagerInterface)
	: UComponent(InComponentManagerInterface)
	, bHasTargetMoveToLocation(false)
	, StopDistance(0.f)
	, LinearSpeedPerSecond(40.f)
	, AngularSpeedPerSecond(45.f)
	, bHasCustomStopDistance(false)
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
		CurrentLocation = RootTransformComponent->GetLocation();
		CalculatedTargetLocation = TargetLocation + RootTransformComponent->GetLocationMap();

		UpdateRotation(DeltaTime);

		UpdateLocation(DeltaTime);
	}
}

void UMoveComponent::Render()
{
	UComponent::Render();

#if _DEBUG
	// Draw line
	FRenderer* Renderer = GetOwnerWindow()->GetRenderer();

	Renderer->DrawLine(CurrentLocation, CalculatedTargetLocation);
#endif
}

void UMoveComponent::SetStoppingDistance(const float InStopDistance)
{
	StopDistance = InStopDistance;

	bHasCustomStopDistance = true;
}

void UMoveComponent::ResetStoppingDistance()
{
	bHasCustomStopDistance = false;
}

void UMoveComponent::SetTargetMoveLocation(const FVector2D<int> NewTargetLocation)
{
	PreciseLocation = RootTransformComponent->GetLocationUser();
	PreciseRotation = static_cast<float>(RootTransformComponent->GetRotation());

	TargetLocation = NewTargetLocation;

	bHasTargetMoveToLocation = true;

	if (!bHasCustomStopDistance)
	{
		StopDistance = 0.f;
	}
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

		if (RootTransformComponent->GetLocationUser().DistanceTo(TargetLocation) < Distance)
		{
			RootTransformComponent->SetLocationUser(TargetLocation);
		}
		else
		{
			const FVector2D<float> LocationToMove = CurrentVector * Distance;
			PreciseLocation += LocationToMove;

			RootTransformComponent->SetLocationUser(PreciseLocation);
		}
	}
}

void UMoveComponent::UpdateRotation(const float DeltaTime)
{
	const float TargetRotation = FMath::FindLookAtRotationInDegrees(CurrentLocation, CalculatedTargetLocation) + 90;
	const float RotationChangeInCurrentTick = AngularSpeedPerSecond * DeltaTime;

	if (FMath::IsNearlyEqual(PreciseRotation, TargetRotation, RotationChangeInCurrentTick))
	{
		PreciseRotation = TargetRotation;
	}
	else
	{
		const float RotationDiff = TargetRotation - PreciseRotation;

		if (RotationDiff > 0)
		{
			PreciseRotation += RotationChangeInCurrentTick;
		}
		else
		{
			PreciseRotation -= RotationChangeInCurrentTick;
		}
	}

	RootTransformComponent->SetRotation(static_cast<int>(PreciseRotation));
}

void UMoveComponent::UpdateLocation(const float DeltaTime)
{
	const float CurrentDistance = CurrentLocation.DistanceTo(TargetLocation);

	if (CurrentDistance < StopDistance)
	{
		// We are close enough. Stop.
		AbortMovement();
	}
	else
	{
		// Move to TargetLocation
		MoveByUnits(LinearSpeedPerSecond * DeltaTime);
	}
}
