// Created by Przemys³aw Wiewióra 2020-2024

#include "CoreEngine.h"
#include "Core/ECS/Components/CircleCollisionComponent.h"

#include "ECS/Collision/CircleCollision.h"
#include "ECS/Collision/CollisionManager.h"

UCircleCollisionComponent::UCircleCollisionComponent(IComponentManagerInterface* InComponentManagerInterface)
	: UCollisionComponent(InComponentManagerInterface)
	, CircleCollision(nullptr)
{
}

UCircleCollisionComponent::~UCircleCollisionComponent()
{
	delete CircleCollision;
}

void UCircleCollisionComponent::BeginPlay()
{
	Super::BeginPlay();

	CircleCollision = new FCircleCollision(GetLocationCenter(), GetCircleRadius());
}

void UCircleCollisionComponent::Render()
{
	Super::Render();

#if _DEBUG
	// Draw collision
	if (CircleCollision != nullptr && CollisionManagerCached != nullptr && CollisionManagerCached->IsDebugEnabled())
	{
		FRenderer* Renderer = GetOwnerWindow()->GetRenderer();
		const FCircleCollisionData& CircleData = CircleCollision->GetCircleCollisionData();

		Renderer->DrawCircle(CircleData.GetLocation(), CircleData.GetRadius());
	}
#endif
}

void UCircleCollisionComponent::OnTransformLocationChanged()
{
	UCollisionComponent::OnTransformLocationChanged();

	FCircleCollisionData& CircleCollisionDataForEdit = CircleCollision->GetCircleCollisionDataForEdit();
	CircleCollisionDataForEdit.UpdateLocation(GetLocationCenter());
}

int UCircleCollisionComponent::GetCircleRadius() const
{
	FVector2D<int> Size = GetSize();

	return FMath::Max(Size.X, Size.Y) / 2;
}

FVector2D<int> UCircleCollisionComponent::GetLocationForCollision() const
{
	return GetLocationCenter();
}
