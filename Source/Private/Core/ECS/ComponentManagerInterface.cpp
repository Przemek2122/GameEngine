// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "ECS/ComponentManagerInterface.h"

IComponentManagerInterface::IComponentManagerInterface(IComponentManagerInterface* InComponentManagerInterfaceParent, FWindow* InOwnerWindow)
	: ComponentManagerInterfaceParent(InComponentManagerInterfaceParent)
	, bDoesHaveComponentManagerInterfaceParent(InComponentManagerInterfaceParent != nullptr)
	, OwnerWindow(InOwnerWindow)
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
		ComponentsMap[ComponentName]->EndPlay();

		OnComponentDestroy(ComponentName, ComponentsMap[ComponentName].get());

		ComponentsMap[ComponentName].reset();

		ComponentsMap.Remove(ComponentName);

		return true;
	}

	return false;
}

bool IComponentManagerInterface::DestroyComponentByInstance(const UComponent* Component)
{
	for (std::pair<const std::string, std::shared_ptr<UComponent>>& ComponentPair : ComponentsMap)
	{
		if (ComponentPair.second.get() == Component)
		{
			ComponentPair.second->EndPlay();

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

FWindow* IComponentManagerInterface::GetOwnerWindow() const
{
	return OwnerWindow;
}

void IComponentManagerInterface::TickComponents()
{
	for (const auto& [ComponentName, Component] : ComponentsMap)
	{
		if (Component->IsComponentActive())
		{
			Component->Tick();
		}
	}
}

void IComponentManagerInterface::RenderComponents()
{
	for (const auto& [ComponentName, Component] : ComponentsMap)
	{
		if (Component->IsComponentActive())
		{
			Component->Render();
		}
	}
}
