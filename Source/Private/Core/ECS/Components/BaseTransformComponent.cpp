// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "ECS/Components/BaseTransformComponent.h"
#include "Renderer/Map/Map.h"
#include "Renderer/Map/MapManager.h"

UBaseTransformComponent::UBaseTransformComponent(IComponentManagerInterface* InComponentManagerInterface)
	: UBaseComponent(InComponentManagerInterface)
	, Size(32, 32)
{
}

void UBaseTransformComponent::BeginPlay()
{
	UBaseComponent::BeginPlay();

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
	UBaseComponent::EndPlay();

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

void UBaseTransformComponent::OnComponentCreated(const std::string& ComponentName, UBaseComponent* NewComponent)
{
	Super::OnComponentCreated(ComponentName, NewComponent);

	ITransformChildInterface2D<int>* TransformComponent = dynamic_cast<ITransformChildInterface2D<int>*>(NewComponent);
	if (TransformComponent != nullptr)
	{
		AddUpdatedComponent(TransformComponent);

		// Update location of new component
		TransformComponent->SetLocationFromParent(GetLocation());
		TransformComponent->SetParentRotation(GetRotation());
	}
}

void UBaseTransformComponent::OnComponentDestroy(const std::string& ComponentName, UBaseComponent* OldComponent)
{
	Super::OnComponentDestroy(ComponentName, OldComponent);

	ITransformChildInterface2D<int>* TransformComponent = dynamic_cast<ITransformChildInterface2D<int>*>(OldComponent);
	if (TransformComponent != nullptr)
	{
		RemoveUpdatedComponent(TransformComponent);
	}
}

FVector2D<float> UBaseTransformComponent::GetForwardVector() const
{
	static const FVector2D<float> ForwardVector = { 0, -1 };
	constexpr float VectorRotation = 360;

	FVector2D<int> CurrentForwardVector = ForwardVector * VectorRotation;

	const int CurrentRotation = GetRotation();
	const float CurrentRotationRadian = FMath::DegreesToRadians(static_cast<float>(CurrentRotation));

	FMath::RotatePointAroundPoint({ 0, 0 }, CurrentRotationRadian, CurrentForwardVector);

	return FVector2D<float>(CurrentForwardVector) / VectorRotation;
}

FVector2D<float> UBaseTransformComponent::GetRightVector() const
{
	static const FVector2D<float> RightVector = { 1, 0 };

	FVector2D<int> CurrentRightVector = RightVector;

	FMath::RotatePointAroundPoint({ 0, 0 }, static_cast<float>(GetRotation()), CurrentRightVector);

	return RightVector;
}

FVector2D<int> UBaseTransformComponent::GetLocationCenter() const
{
	return (GetLocation() + (Size / 2));
}

FVector2D<int> UBaseTransformComponent::GetSize() const
{
	return Size;
}

void UBaseTransformComponent::OnMapLocationChanged(const FVector2D<int> NewLocation)
{
	SetLocationMap(NewLocation);
}
