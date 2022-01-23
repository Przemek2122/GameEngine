// Created by Przemys³aw Wiewióra 2020

#pragma once

class UComponent;

class IComponentManagerInterface
{
protected:
	IComponentManagerInterface(IComponentManagerInterface* InComponentManagerInterfaceParent);
	virtual ~IComponentManagerInterface();

public:
	template<class TComponentClass, typename... TInParams>
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
				return ComponentPair.second;
			}
		}

		return nullptr;
	}

	/** Called when new component is created. */
	virtual void OnComponentCreated(const std::string& ComponentName, UComponent* NewComponent);
	/** Called before destroying component. */
	virtual void OnComponentDestroy(const std::string& ComponentName, UComponent* OldComponent);

	/** @returns true if has owner and GetOwner() is safe to call. */
	_NODISCARD bool HasOwner() const { return bDoesHaveComponentManagerInterfaceParent; }
	/** @return cached owner. */
	_NODISCARD IComponentManagerInterface* GetOwner() const;
	/** Iterate all elements to the top returning top level owner, most likely EEntity. */
	_NODISCARD IComponentManagerInterface* GetOwnerTop() const;

protected:
	/** Parent, could be other component or  */
	IComponentManagerInterface* ComponentManagerInterfaceParent;
	/** Components accessible by strings passed when creating components which are component names. */
	CUnorderedMap<std::string, std::shared_ptr<UComponent>> ComponentsMap;
	/** Cached in constructor (ComponentManagerInterfaceParent != nullptr) */
	bool bDoesHaveComponentManagerInterfaceParent;

};