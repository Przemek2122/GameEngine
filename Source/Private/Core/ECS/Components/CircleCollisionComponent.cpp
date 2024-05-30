// Created by Przemys³aw Wiewióra 2020-2024

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
}

void UCircleCollisionComponent::Init()
{
	UCollisionComponent::Init();

	CircleCollision = new FCircleCollision(GetCircleRadius());
}

void UCircleCollisionComponent::Tick(const float DeltaTime)
{
	UCollisionComponent::Tick(DeltaTime);

#if _DEBUG
	if (CircleCollision != nullptr)
	{
		
	}
#endif
}

int UCircleCollisionComponent::GetCircleRadius() const
{
	FVector2D<int> Size = GetSize();

	return FMath::Max(Size.X, Size.Y) / 2;
}
