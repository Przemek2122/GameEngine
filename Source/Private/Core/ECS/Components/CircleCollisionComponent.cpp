// Created by Przemys�aw Wiewi�ra 2020-2024

#include "CoreEngine.h"
#include "Core/ECS/Components/CircleCollisionComponent.h"

#include "ECS/Collision/CircleCollision.h"

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

	CircleCollision = new FCircleCollision(GetLocation(), GetCircleRadius());
}

void UCircleCollisionComponent::Render()
{
	Super::Render();

#if _DEBUG
	// Draw collision
	if (CircleCollision != nullptr)
	{
		FRenderer* Renderer = GetOwnerWindow()->GetRenderer();
		const FCircleCollisionData& CircleData = CircleCollision->GetCircleCollisionData();

		Renderer->DrawCircle(CircleData.GetLocation(), CircleData.GetRadius());
	}
#endif
}

int UCircleCollisionComponent::GetCircleRadius() const
{
	FVector2D<int> Size = GetSize();

	return FMath::Max(Size.X, Size.Y) / 2;
}
