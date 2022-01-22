// Created by Przemys�aw Wiewi�ra 2020

#pragma once

#include "ECS/Component.h"

class FEntityManager;

class EEntity : public UObject, public IComponentManagerInterface
{
	friend FEntityManager;
protected:
	EEntity(FEntityManager* InEntityManager);
	virtual ~EEntity() override;

protected:
	FEntityManager* EntityManagerOwner;
};
