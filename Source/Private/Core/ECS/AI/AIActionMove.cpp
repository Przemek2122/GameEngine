// Created by Przemys³aw Wiewióra 2024

#include "CoreEngine.h"
#include "Core/ECS/AI/AIActionMove.h"

#include "ECS/Components/MoveComponent.h"

FAiActionMove::FAiActionMove(FAiTree* InAiTree)
	: FAiActionBase(InAiTree)
	, CurrentMoveComponent(nullptr)
{
}

bool FAiActionMove::ShouldFinishAction() const
{
	return (CurrentMoveComponent != nullptr && !CurrentMoveComponent->IsMoving());
}

void FAiActionMove::StartAction()
{
	Super::StartAction();

	// Get entity. Should always be valid.
	EEntity* Entity = GetTree()->GetOwnerEntity();

	// Move component does not have to be present.
	CurrentMoveComponent = Entity->GetComponentByClass<UMoveComponent>();
	if (CurrentMoveComponent != nullptr)
	{
		
	}
}

void FAiActionMove::EndAction()
{
	Super::EndAction();

	if (CurrentMoveComponent != nullptr && CurrentMoveComponent->IsMoving())
	{
		CurrentMoveComponent->AbortMovement();
		CurrentMoveComponent = nullptr;
	}
}
