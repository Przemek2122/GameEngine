// Created by Przemys³aw Wiewióra 2020-2022

#pragma once

#include "ECS/Entity.h"

class FEntityManager
{
	friend FWindow;

protected:
	FEntityManager();
	virtual ~FEntityManager();

public:
	template<typename TEntityClass, typename... TInParams>
	TEntityClass* CreateEntity(std::string EntityName, TInParams... InParams)
	{
		auto NewEntity = std::make_shared<TEntityClass>(this, InParams);

		EntitiesMap.Emplace(EntityName, NewEntity);

		OnEntityCreated(EntityName, NewEntity);

		return NewEntity.get();
	}

	bool DestroyEntityByName(const std::string& EntityName);
	bool DestroyEntityByInstance(EEntity* Entity);

	virtual void OnEntityCreated(const std::string& EntityName, EEntity* Entity);
	virtual void OnEntityDestroyed(const std::string& EntityName, EEntity* Entity);

protected:
	CUnorderedMap<std::string, std::shared_ptr<EEntity>> EntitiesMap;
};
