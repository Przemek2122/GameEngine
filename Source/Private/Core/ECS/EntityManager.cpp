// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "ECS/EntityManager.h"

FEntityManager::FEntityManager()
{
}

FEntityManager::~FEntityManager()
{
}

bool FEntityManager::DestroyEntityByName(const std::string& EntityName)
{
	for (std::pair<const std::string, std::shared_ptr<EEntity>>& EntityPair : EntitiesMap)
	{
		OnEntityDestroyed(EntityPair.first, EntityPair.second.get());

		EntitiesMap[EntityName].reset();

		EntitiesMap.Remove(EntityPair.first);
	}

	return false;
}

bool FEntityManager::DestroyEntityByInstance(EEntity* Entity)
{
	for (std::pair<const std::string, std::shared_ptr<EEntity>>& EntityPair : EntitiesMap)
	{
		if (EntityPair.second.get() == Entity)
		{
			OnEntityDestroyed(EntityPair.first, EntityPair.second.get());

			EntityPair.second.reset();

			EntitiesMap.Remove(EntityPair.first);
		}
	}

	return false;
}

void FEntityManager::OnEntityCreated(const std::string& EntityName, EEntity* Entity)
{
}

void FEntityManager::OnEntityDestroyed(const std::string& EntityName, EEntity* Entity)
{
}
