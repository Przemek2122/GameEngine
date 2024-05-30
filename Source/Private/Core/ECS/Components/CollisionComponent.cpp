// Created by Przemys³aw Wiewióra 2024

#include "CoreEngine.h"
#include "ECS/Components/CollisionComponent.h"

#include "ECS/Collision/CollisionManager.h"

UCollisionComponent::UCollisionComponent(IComponentManagerInterface* InComponentManagerInterface)
	: UBaseTransformComponent(InComponentManagerInterface)
	, CollisionManagerCached(nullptr)
{
}

void UCollisionComponent::Init()
{
	UBaseTransformComponent::Init();

	CollisionManagerCached = GetCollisionManager();
}

void UCollisionComponent::AddCollision(FCollisionBase* CollisionObject)
{
	if (CollisionManagerCached != nullptr)
	{
		CollisionObjectsArray.Push(CollisionObject);

		CollisionManagerCached->RegisterCollision(CollisionObject);
	}
	else
	{
		LOG_ERROR("Missing CollisionManager. Collision will not work.");
	}
}

void UCollisionComponent::RemoveCollision(FCollisionBase* CollisionObject)
{
	if (CollisionManagerCached != nullptr)
	{
		CollisionObjectsArray.Remove(CollisionObject);

		CollisionManagerCached->UnRegisterCollision(CollisionObject);
	}
	else
	{
		LOG_ERROR("Missing CollisionManager. Collision will not work.");
	}
}

void UCollisionComponent::OnTransformLocationChanged(const ELocationChangeType LocationChangeType)
{
	UBaseTransformComponent::OnTransformLocationChanged(LocationChangeType);

	if (CollisionManagerCached != nullptr)
	{
		// Send notification about changed collision to CollisionManager
		for (FCollisionBase* CollisionObjects : CollisionObjectsArray)
		{
			CollisionManagerCached->OnCollisionObjectMoved(CollisionObjects);
		}
	}
	else
	{
		LOG_ERROR("Missing CollisionManager. Collision will not update.");
	}
}

const CArray<FCollisionBase*>& UCollisionComponent::GetCollisionObjectsArray() const
{
	return CollisionObjectsArray;
}

FCollisionManager* UCollisionComponent::GetCollisionManager() const
{
	return GetOwnerWindow()->GetSubSystemByClass<FCollisionManager>();
}

#if _DEBUG
FColorRGBA UCollisionComponent::GetCollisionDebugColor()
{
	static FColorRGBA CollisionDebugColor = FColorRGBA::ColorLightGreen();

	return CollisionDebugColor;
}
#endif