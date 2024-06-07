// Created by Przemys³aw Wiewióra 2024

#include "CoreEngine.h"
#include "ECS/Components/CollisionComponent.h"

#include "ECS/Collision/CollisionManager.h"
#include "Renderer/Map/Map.h"
#include "Renderer/Map/MapManager.h"

UCollisionComponent::UCollisionComponent(IComponentManagerInterface* InComponentManagerInterface)
	: UComponent(InComponentManagerInterface)
	, CollisionManagerCached(nullptr)
{
}

void UCollisionComponent::BeginPlay()
{
	Super::BeginPlay();

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

void UCollisionComponent::OnTransformLocationChanged()
{
	Super::OnTransformLocationChanged();

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

void UCollisionComponent::OnCollisionBegin(UCollisionComponent* OtherCollision)
{
	LOG_INFO("C Start");
}

void UCollisionComponent::OnCollisionEnd(UCollisionComponent* OtherCollision)
{
	LOG_INFO("C End");
}

FCollisionManager* UCollisionComponent::GetCollisionManager() const
{
	FCollisionManager* FoundCollisionManager = nullptr;

	FMapManager* MapManager = GetOwnerWindow()->GetMapManager();
	if (MapManager != nullptr)
	{
		FMap* CurrentMap = MapManager->GetCurrentMap();
		if (CurrentMap != nullptr)
		{
			FoundCollisionManager = CurrentMap->GetSubSystemByClass<FCollisionManager>();
		}
	}

	return FoundCollisionManager;
}

FVector2D<int> UCollisionComponent::GetLocationForCollision() const
{
	return GetLocation();
}

#if _DEBUG
FColorRGBA UCollisionComponent::GetCollisionDebugColor()
{
	static FColorRGBA CollisionDebugColor = FColorRGBA::ColorLightGreen();

	return CollisionDebugColor;
}
#endif