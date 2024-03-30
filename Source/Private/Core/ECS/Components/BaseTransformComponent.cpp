// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "ECS/Components/BaseTransformComponent.h"
#include "Renderer/Map/Map.h"
#include "Renderer/Map/MapManager.h"

UBaseTransformComponent::UBaseTransformComponent(IComponentManagerInterface* InComponentManagerInterface)
	: UComponent(InComponentManagerInterface)
	, Size(32, 32)
{
}

void UBaseTransformComponent::BeginPlay()
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
				CurrentMap->GetMapLocationChangeDelegate().BindObject(this, &UBaseTransformComponent::OnMapLocationChanged);
			}
			else
			{
				LOG_ERROR("UBaseTransformComponent::BeginPlay: CurrentMap is nullptr");
			}
		}
		else
		{
			LOG_ERROR("UBaseTransformComponent::BeginPlay: MapManager is nullptr");
		}
	}
	else
	{
		LOG_ERROR("UBaseTransformComponent::BeginPlay: Window is nullptr");
	}
}

void UBaseTransformComponent::EndPlay()
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
				CurrentMap->GetMapLocationChangeDelegate().UnBindObject(this, &UBaseTransformComponent::OnMapLocationChanged);
			}
		}
	}
}

void UBaseTransformComponent::OnComponentCreated(const std::string& ComponentName, UComponent* NewComponent)
{
	Super::OnComponentCreated(ComponentName, NewComponent);

	ITransformChildInterface2D<int>* TransformComponent = dynamic_cast<ITransformChildInterface2D<int>*>(NewComponent);
	if (TransformComponent != nullptr)
	{
		AddUpdatedComponent(TransformComponent);

		// Update location of new component
		TransformComponent->SetLocationFromParent(GetLocation());
	}
}

void UBaseTransformComponent::OnComponentDestroy(const std::string& ComponentName, UComponent* OldComponent)
{
	Super::OnComponentDestroy(ComponentName, OldComponent);

	ITransformChildInterface2D<int>* TransformComponent = dynamic_cast<ITransformChildInterface2D<int>*>(OldComponent);
	if (TransformComponent != nullptr)
	{
		RemoveUpdatedComponent(TransformComponent);
	}
}

FVector2D<int> UBaseTransformComponent::GetSize() const
{
	return Size;
}

void UBaseTransformComponent::OnMapLocationChanged(const FVector2D<int> NewLocation)
{
	SetLocationMap(NewLocation);
}
