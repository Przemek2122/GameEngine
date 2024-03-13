// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "ECS/ComponentManagerInterface.h"

IComponentManagerInterface::IComponentManagerInterface(IComponentManagerInterface* InComponentManagerInterfaceParent)
	: ComponentManagerInterfaceParent(InComponentManagerInterfaceParent)
	, bDoesHaveComponentManagerInterfaceParent(InComponentManagerInterfaceParent != nullptr)
{
}

IComponentManagerInterface::~IComponentManagerInterface()
{
	ComponentsMap.Clear();
}

bool IComponentManagerInterface::DestroyComponent(const std::string& ComponentName)
{
	if (ComponentsMap.IsValidKey(ComponentName))
	{
		OnComponentDestroy(ComponentName, ComponentsMap[ComponentName].get());

		ComponentsMap[ComponentName].reset();

		ComponentsMap.Remove(ComponentName);

		return true;
	}

	return false;
}

bool IComponentManagerInterface::DestroyComponentByInstance(UComponent* Component)
{
	for (std::pair<const std::string, std::shared_ptr<UComponent>>& ComponentPair : ComponentsMap)
	{
		if (ComponentPair.second.get() == Component)
		{
			OnComponentDestroy(ComponentPair.first, ComponentPair.second.get());

			ComponentPair.second.reset();

			ComponentsMap.Remove(ComponentPair.first);

			return true;
		}
	}

	return false;
}

void IComponentManagerInterface::OnComponentCreated(const std::string& ComponentName, UComponent* NewComponent)
{
}

void IComponentManagerInterface::OnComponentDestroy(const std::string& ComponentName, UComponent* OldComponent)
{
}

IComponentManagerInterface* IComponentManagerInterface::GetOwner() const
{
	return ComponentManagerInterfaceParent;
}

IComponentManagerInterface* IComponentManagerInterface::GetOwnerTop() const
{
	IComponentManagerInterface* CurrentChainElement = ComponentManagerInterfaceParent;

	if (CurrentChainElement->HasOwner())
	{
		CurrentChainElement = CurrentChainElement->GetOwner();
	}

	return CurrentChainElement;
}

void IComponentManagerInterface::TickComponents()
{
	for (const auto& [ComponentName, Component] : ComponentsMap)
	{
		Component->Tick();
	}
}

void IComponentManagerInterface::RenderComponents()
{
	for (const auto& [ComponentName, Component] : ComponentsMap)
	{
		Component->Render();
	}
}
