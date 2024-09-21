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
	return false;
}

void FAIActionMove::StartAction()
{
	Super::StartAction();
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
