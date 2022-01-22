// Created by Przemys³aw Wiewióra 2020

#pragma once

class UComponent;

class IComponentManagerInterface
{
protected:
	IComponentManagerInterface();
	virtual ~IComponentManagerInterface();

public:
	template<typename TComponentClass, typename... TInParams>
	TComponentClass* CreateComponent(std::string ComponentName, TInParams... InParams)
	{
		auto NewComponent = std::make_shared<TComponentClass>(this, InParams);

		ComponentsMap.Emplace(ComponentName, NewComponent);

		OnComponentCreated(ComponentName, NewComponent);

		return NewComponent.get();
	}

	bool DestroyComponent(const std::string& ComponentName);
	bool DestroyComponentByInstance(UComponent* Component);
	
	template<typename TComponentClass = UComponent>
	TComponentClass* GetComponent(std::string ComponentName)
	{
		if (ComponentsMap.IsValidKey(ComponentName))
		{
			return ComponentsMap[ComponentName];
		}

		return nullptr;
	}
	template<typename TComponentClass = UComponent>
	TComponentClass* GetComponent(const std::string& ComponentName)
	{
		if (ComponentsMap.IsValidKey(ComponentName))
		{
			return ComponentsMap[ComponentName];
		}

		return nullptr;
	}
	template<typename TComponentClass>
	TComponentClass* GetComponentByClass()
	{
		for (std::pair<const std::string, std::shared_ptr<UComponent>>& ComponentPair : ComponentsMap)
		{
			if (typeid(ComponentPair.second) == typeid(TComponentClass))
			{
				
			}
		}

		return nullptr;
	}

	/** Called when new component is created. */
	virtual void OnComponentCreated(const std::string& ComponentName, UComponent* NewComponent);
	/** Called before destroying component. */
	virtual void OnComponentDestroy(const std::string& ComponentName, UComponent* OldComponent);

protected:
	CUnorderedMap<std::string, std::shared_ptr<UComponent>> ComponentsMap;

};