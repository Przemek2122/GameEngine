// Created by Przemys�aw Wiewi�ra 2020

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
