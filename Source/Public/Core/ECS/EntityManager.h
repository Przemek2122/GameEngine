// Created by Przemys³aw Wiewióra 2020-2023

#pragma once

#include "ECS/Entity.h"

class FEntityManager
{
	friend FWindow;

protected:
	FEntityManager(FWindow* InOwnerWindow);
	virtual ~FEntityManager();

public:
	template<typename TEntityClass, typename... TInParams>
	TEntityClass* CreateEntity(std::string EntityName, TInParams... InParams)
	{
		TEntityClass* NewEntity = new TEntityClass(this, InParams ...);

		Entities.Push(NewEntity);

		NewEntity->BeginPlay();

		OnEntityCreated(NewEntity);

		return NewEntity;
	}

	bool DestroyEntity(const EEntity* Entity);

	FWindow* GetOwnerWindow() const { return OwnerWindow; }

	virtual void Tick(float DeltaTime);
	virtual void Render();

protected:
	virtual void OnEntityCreated(EEntity* Entity);
	virtual void OnEntityPreDestroyed(EEntity* Entity);

private:
	/** Array with entites */
	CArray<EEntity*> Entities;

	/** Owner window */
	FWindow* OwnerWindow;

};
