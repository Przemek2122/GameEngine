// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "ECS/Component.h"

UComponent::UComponent(IComponentManagerInterface* InComponentManagerInterface)
	: UBaseComponent(InComponentManagerInterface)
{
}

void UComponent::OnComponentCreated(const std::string& ComponentName, UBaseComponent* NewComponent)
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

void UComponent::OnComponentDestroy(const std::string& ComponentName, UBaseComponent* OldComponent)
{
	Super::OnComponentDestroy(ComponentName, OldComponent);

	ITransformChildInterface2D<int>* TransformComponent = dynamic_cast<ITransformChildInterface2D<int>*>(OldComponent);
	if (TransformComponent != nullptr)
	{
		RemoveUpdatedComponent(TransformComponent);
	}
}

FVector2D<int> UComponent::GetSize() const
{
	FVector2D<int> FinalSize;

	UBaseComponent* RootComponent = GetRootComponentOfEntity();
	if (UParentComponent* ParentRootComponent = dynamic_cast<UParentComponent*>(RootComponent))
	{
		FinalSize = ParentRootComponent->GetSize();
	}

	return FinalSize;
}

FVector2D<int> UComponent::GetLocationCenter() const
{
	return FMath::GetLocationCenter(GetLocation(), GetSize());
}
