// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "ECS/Entity.h"

EEntity::EEntity(FEntityManager* InEntityManager)
	: IComponentManagerInterface(nullptr)
	, EntityManagerOwner(InEntityManager)
{
#if _DEBUG
	if (InEntityManager != nullptr)
	{
		LOG_INFO("Entity created. (" << GetCppClassName() << ")");
	}
#endif
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

FEntityManager* EEntity::GetEntityManagerOwner() const
{
	return EntityManagerOwner;
}

FWindow* EEntity::GetWindow() const
{
	return EntityManagerOwner->GetOwnerWindow();
}
