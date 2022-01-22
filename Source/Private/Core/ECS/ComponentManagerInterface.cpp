// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "ECS/ComponentManagerInterface.h"

IComponentManagerInterface::IComponentManagerInterface()
{
}

IComponentManagerInterface::~IComponentManagerInterface()
{
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
