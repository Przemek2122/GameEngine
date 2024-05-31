// Created by Przemys³aw Wiewióra 2020-2024

#include "CoreEngine.h"
#include "Core/ECS/Components/SquareCollisionComponent.h"

#include "ECS/Collision/CollisionManager.h"
#include "ECS/Collision/SquareCollision.h"

USquareCollisionComponent::USquareCollisionComponent(IComponentManagerInterface* InComponentManagerInterface)
	: UCollisionComponent(InComponentManagerInterface)
	, SquareCollision(nullptr)
{
}

USquareCollisionComponent::~USquareCollisionComponent()
{
	delete SquareCollision;
}

void USquareCollisionComponent::BeginPlay()
{
	Super::BeginPlay();

	SquareCollision = new FSquareCollision(GetLocation(), GetSize());

	AddCollision(SquareCollision);
}

void USquareCollisionComponent::Render()
{
	Super::Render();

#if _DEBUG
	// Draw collision
	if (SquareCollision != nullptr && CollisionManagerCached != nullptr && CollisionManagerCached->IsDebugEnabled())
	{
		FRenderer* Renderer = GetOwnerWindow()->GetRenderer();

		const FSquareData& SquareData = SquareCollision->GetSquareData();

		Renderer->DrawRectangleOutline(SquareData.GetLocation(), SquareData.GetSize(), GetCollisionDebugColor());
	}
#endif
}

void USquareCollisionComponent::OnTransformLocationChanged()
{
	Super::OnTransformLocationChanged();

	// Update location
	FSquareData& SquareDataForEdit = SquareCollision->GetSquareDataForEdit();
	SquareDataForEdit.UpdateLocation(GetLocation());
}

void USquareCollisionComponent::OnTransformRotationChanged()
{
	Super::OnTransformRotationChanged();

	// @TODO Rotation of square collision
}
