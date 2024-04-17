// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "ECS/Component.h"

UComponent::UComponent(IComponentManagerInterface* InComponentManagerInterface)
	: IComponentManagerInterface(InComponentManagerInterface, InComponentManagerInterface->GetOwnerWindow())
	, bIsComponentActive(true)
{
}

void UComponent::BeginPlay()
{
	ActivateComponent();
}

void UComponent::EndPlay()
{
	DeactivateComponent();
}

void UComponent::Tick(const float DeltaTime)
{
	// Tick sub-components
	TickComponents(DeltaTime);
}

void UComponent::Render()
{
	// Render sub-components
	RenderComponents();
}

void UComponent::ActivateComponent()
{
	bIsComponentActive = true;
}

void UComponent::DeactivateComponent()
{
	bIsComponentActive = false;
}

bool UComponent::IsComponentActive() const
{
	return bIsComponentActive;
}
