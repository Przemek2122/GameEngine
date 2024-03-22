// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "ECS/Components/TransformComponent.h"
#include "Renderer/Map/Map.h"
#include "Renderer/Map/MapManager.h"

UTransformComponent::UTransformComponent(IComponentManagerInterface* InComponentManagerInterface)
	: UComponent(InComponentManagerInterface)
	, Size(32, 32)
{
}

void UTransformComponent::BeginPlay()
{
	UComponent::BeginPlay();

	const FWindow* Window = GetOwnerWindow();
	if (Window != nullptr)
	{
		const FMapManager* MapManger = Window->GetMapManager();
		if (MapManger != nullptr)
		{
			FMap* CurrentMap = MapManger->GetCurrentMap();
			if (CurrentMap != nullptr)
			{
				CurrentMap->GetMapLocationChangeDelegate().BindObject(this, &UTransformComponent::OnMapLocationChanged);
			}
			else
			{
				LOG_ERROR("UTransformComponent::BeginPlay: CurrentMap is nullptr");
			}
		}
		else
		{
			LOG_ERROR("UTransformComponent::BeginPlay: MapManager is nullptr");
		}
	}
	else
	{
		LOG_ERROR("UTransformComponent::BeginPlay: Window is nullptr");
	}
}

void UTransformComponent::EndPlay()
{
	UComponent::EndPlay();

	const FWindow* Window = GetOwnerWindow();
	if (Window != nullptr)
	{
		const FMapManager* MapManger = Window->GetMapManager();
		if (MapManger != nullptr)
		{
			FMap* CurrentMap = MapManger->GetCurrentMap();
			if (CurrentMap != nullptr)
			{
				CurrentMap->GetMapLocationChangeDelegate().UnBindObject(this, &UTransformComponent::OnMapLocationChanged);
			}
		}
	}
}

FVector2D<int> UTransformComponent::GetSize() const
{
	return Size;
}

void UTransformComponent::OnTransformLocationChanged(const ELocationChangeType LocationChangeType)
{
	ITransformInterface2D<int>::OnTransformLocationChanged(LocationChangeType);

	OnLocationChanged.Execute(GetLocationFinal());
}

void UTransformComponent::OnMapLocationChanged(const FVector2D<int> NewLocation)
{
	SetLocationMap(NewLocation);
}
