// Created by Przemys�aw Wiewi�ra 2020

#include "CoreEngine.h"
#include "ECS/Entity.h"

EEntity::EEntity(FEntityManager* InEntityManager)
	: IComponentManagerInterface(nullptr)
	, EntityManagerOwner(InEntityManager)
{
}

EEntity::~EEntity()
{
}

void EEntity::BeginPlay()
{
}

void EEntity::EndPlay()
{
}
