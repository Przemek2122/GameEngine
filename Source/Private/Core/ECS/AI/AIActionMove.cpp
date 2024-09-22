// Created by Przemys³aw Wiewióra 2024

#include "CoreEngine.h"
#include "Core/ECS/AI/AIActionMove.h"

#include "ECS/Components/MoveComponent.h"

FAIActionMove::FAIActionMove(FAITree* InAiTree)
	: FAIActionBase(InAiTree)
	, CurrentMoveComponent(nullptr)
{
}

void FAIActionMove::Initialize()
{
	Super::Initialize();

	// Get entity. Should always be valid.
	EEntity* Entity = GetTree()->GetOwnerEntity();

	// Move component does not have to be present.
	CurrentMoveComponent = Entity->GetComponentByClass<UMoveComponent>();
	if (CurrentMoveComponent == nullptr)
	{
		LOG_WARN("Missing MoveComponent in FAIActionMove, Entity class: " << Entity->GetCppClassNameWithoutClass());
	}
}

bool FAIActionMove::ShouldFinishAction() const
{
	return (CurrentMoveComponent != nullptr && !CurrentMoveComponent->IsMoving());
}

bool FAIActionMove::IsActionReady() const
{
	return true;
}

void FAIActionMove::StartAction()
{
	Super::StartAction();

	if (CurrentMoveComponent != nullptr)
	{
		CurrentMoveComponent->OnStoppedMovement.BindObject(this, &FAIActionMove::OnStoppedMovement);
	}
}

void FAIActionMove::EndAction()
{
	Super::EndAction();

	if (CurrentMoveComponent != nullptr && CurrentMoveComponent->IsMoving())
	{
		CurrentMoveComponent->AbortMovement();
		CurrentMoveComponent = nullptr;
	}
}

void FAIActionMove::SetTargetLocation(const FVector2D<int>& NewLocation) const
{
	if (CurrentMoveComponent != nullptr)
	{
		CurrentMoveComponent->SetTargetMoveLocation(NewLocation);
	}
}

void FAIActionMove::OnStoppedMovement()
{
	if (CurrentMoveComponent != nullptr)
	{
		CurrentMoveComponent->OnStoppedMovement.UnBindObject(this, &FAIActionMove::OnStoppedMovement);
	}

	EndAction();
}
