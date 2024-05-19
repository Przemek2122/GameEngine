// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "ECS/Component.h"

UComponent::UComponent(IComponentManagerInterface* InComponentManagerInterface)
	: UBaseComponent(InComponentManagerInterface)
{
}

void UComponent::OnComponentCreated(const std::string& ComponentName, UBaseComponent* NewComponent)
{
	UBaseComponent::OnComponentCreated(ComponentName, NewComponent);

	ITransformChildInterface2D<int>* TransformComponent = dynamic_cast<ITransformChildInterface2D<int>*>(NewComponent);
	if (TransformComponent != nullptr)
	{
		AddUpdatedComponent(TransformComponent);

		// Update location of new component
		TransformComponent->SetLocationFromParent(GetLocation());
		TransformComponent->SetParentRotation(GetRotation());
	}
}

void UComponent::OnComponentDestroy(const std::string& ComponentName, UBaseComponent* OldComponent)
{
	UBaseComponent::OnComponentDestroy(ComponentName, OldComponent);

	ITransformChildInterface2D<int>* TransformComponent = dynamic_cast<ITransformChildInterface2D<int>*>(OldComponent);
	if (TransformComponent != nullptr)
	{
		RemoveUpdatedComponent(TransformComponent);
	}
}


