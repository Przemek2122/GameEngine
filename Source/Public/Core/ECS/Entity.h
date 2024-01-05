// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "ECS/Component.h"

class FEntityManager;

class EEntity : public UObject, public IComponentManagerInterface
{
public:
	EEntity(FEntityManager* InEntityManager);
	virtual ~EEntity() override;

	virtual void BeginPlay();
	virtual void EndPlay();

protected:
	FEntityManager* EntityManagerOwner;
};
