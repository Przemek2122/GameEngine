// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "ECS/Entity.h"

EEntity::EEntity(FEntityManager* InEntityManager)
	: IComponentManagerInterface(nullptr, InEntityManager->GetOwnerWindow())
	, EntityManagerOwner(InEntityManager)
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

	TickComponents();
}

void EEntity::Render()
{
}

void EEntity::ReceiveRender()
{
	Render();

	RenderComponents();
}

FEntityManager* EEntity::GetEntityManagerOwner() const
{
	return EntityManagerOwner;
}

FWindow* EEntity::GetWindow() const
{
	return EntityManagerOwner->GetOwnerWindow();
}
