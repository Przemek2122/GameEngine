// Created by Przemys³aw Wiewióra 2020

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

void EEntity::Tick(float DeltaTime)
{
}

void EEntity::ReceiveTick(const float DeltaTime)
{
	Tick(DeltaTime);
}
