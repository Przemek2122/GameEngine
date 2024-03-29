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
	RegisterInputInternal();
}

void EEntity::EndPlay()
{
	UnRegisterInputInternal();
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

void EEntity::RegisterInput(const FEventHandler* InputHandler)
{
}

void EEntity::UnRegisterInput(const FEventHandler* InputHandler)
{
}

FEntityManager* EEntity::GetEntityManagerOwner() const
{
	return EntityManagerOwner;
}

FWindow* EEntity::GetWindow() const
{
	return EntityManagerOwner->GetOwnerWindow();
}

void EEntity::RegisterInputInternal()
{
	const FEventHandler* InputHandler = GEngine->GetEventHandler();

	RegisterInput(InputHandler);
}

void EEntity::UnRegisterInputInternal()
{
	const FEventHandler* InputHandler = GEngine->GetEventHandler();

	UnRegisterInput(InputHandler);
}
