// Created by Przemys�aw Wiewi�ra 2020-2024

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

	SquareCollision = new FSquareCollision(this, GetLocation(), GetSize());

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

		const FRectangleWithDiagonal& SquareData = SquareCollision->GetSquareData();

		Renderer->DrawRectangleOutline(SquareData.GetPositionTopLeft(), SquareData.GetSize(), GetCollisionDebugColor());
	}
#endif
}

void USquareCollisionComponent::OnTransformLocationChanged()
{
	Super::OnTransformLocationChanged();

	// Update location
	FRectangleWithDiagonal& SquareDataForEdit = SquareCollision->GetSquareDataForEdit();
	SquareDataForEdit.SetLocationTopLeftCorner(GetLocation());
}

void USquareCollisionComponent::OnTransformRotationChanged()
{
	Super::OnTransformRotationChanged();

	// @TODO Rotation of square collision
}
