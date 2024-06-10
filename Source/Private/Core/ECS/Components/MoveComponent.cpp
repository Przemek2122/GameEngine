// Created by Przemys�aw Wiewi�ra 2020

#include "CoreEngine.h"
#include "ECS/Components/MoveComponent.h"
#include "ECS/Components/ArrowComponent.h"
#include "ECS/Components/ParentComponent.h"
#include "Renderer/Map/Map.h"

UMoveComponent::UMoveComponent(IComponentManagerInterface* InComponentManagerInterface)
	: UComponent(InComponentManagerInterface)
	, bHasTargetMoveToLocation(false)
	, bShouldRotateInstant(false)
	, StopDistance(0.f)
	, LinearSpeedPerSecond(40.f)
	, AngularSpeedPerSecond(90.f)
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

	RootTransformComponent = dynamic_cast<UParentComponent*>(GetRootComponentOfEntity());
}

void UMoveComponent::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (CurrentMovementMethod)
	{
		case EMovementMethod::Default:
		{
			if (bHasTargetMoveToLocation && RootTransformComponent != nullptr)
			{
				CurrentLocation = RootTransformComponent->GetLocation();
				CalculatedTargetLocation = TargetLocation + RootTransformComponent->GetLocationMap();

				UpdateRotationToTarget(DeltaTime);

				UpdateLocationToTarget(DeltaTime);
			}

			break;		
		}
		case EMovementMethod::Linear:
		{
			if (RootTransformComponent != nullptr)
			{
				
			}

			break;
		}
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
	FMap* CurrentMap = GetEntity()->GetCurrentMap();
	if (CurrentMap->IsInBounds(NewTargetLocation))
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
	else
	{
		OnRequestedLocationOutOfBounds();
	}
}

void UMoveComponent::AbortMovement()
{
	TargetLocation = FVector2D<int>();

	bHasTargetMoveToLocation = false;
}

void UMoveComponent::SetShouldRotateInstant(const bool bInShouldRotateInstant)
{
	bShouldRotateInstant = bInShouldRotateInstant;
}

bool UMoveComponent::IsMoving() const
{
	return bHasTargetMoveToLocation;
}

void UMoveComponent::SetMovementMethod(const EMovementMethod NewMovementMethod)
{
	CurrentMovementMethod = NewMovementMethod;
}

void UMoveComponent::SetLinearSpeedPerSecond(const float NewSpeed)
{
	LinearSpeedPerSecond = NewSpeed;
}

void UMoveComponent::SetAngularSpeedPerSecond(const float NewSpeed)
{
	AngularSpeedPerSecond = NewSpeed;
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
				CurrentVector = RootTransformComponent->GetRightVector();

				break;
			}
			case EMovementDirection::Left:
			{
				CurrentVector = -RootTransformComponent->GetRightVector();

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

void UMoveComponent::UpdateRotationToTarget(const float DeltaTime)
{
	// This property is used to never encounter 250 and 4 from next rotation, so we have 360 + 250 and 360 + 4
	static constexpr float FullRotation = 360.f;

	const float TargetRotation = FMath::FindLookAtRotationInDegrees(CurrentLocation, CalculatedTargetLocation);
	const float RotationChangeInCurrentTick = AngularSpeedPerSecond * DeltaTime;

	if (bShouldRotateInstant)
	{
		// Instant rotation to target
		PreciseRotation = TargetRotation;
	}
	else
	{
		if (FMath::IsNearlyEqual(FullRotation + PreciseRotation, FullRotation + TargetRotation, RotationChangeInCurrentTick))
		{
			PreciseRotation = TargetRotation;
		}
		else
		{
			if (FMath::IsNearlyEqual(FullRotation + PreciseRotation + 90.f, FullRotation + TargetRotation, 90.f))
			{
				PreciseRotation += RotationChangeInCurrentTick;
			}
			else
			{
				PreciseRotation -= RotationChangeInCurrentTick;
			}
		}
	}

	PreciseRotation = FMath::ClampAngle(PreciseRotation);

	RootTransformComponent->SetRotation(static_cast<int>(PreciseRotation));
}

void UMoveComponent::UpdateLocationToTarget(const float DeltaTime)
{
	const float CurrentDistance = static_cast<float>(CurrentLocation.DistanceTo(TargetLocation));

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

void UMoveComponent::UpdateLocationLinear(float DeltaTime)
{
	// Move to TargetLocation
	MoveByUnits(LinearSpeedPerSecond * DeltaTime);
}

void UMoveComponent::OnRequestedLocationOutOfBounds()
{
}
