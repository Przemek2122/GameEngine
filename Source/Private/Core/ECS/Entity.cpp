// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "ECS/Entity.h"

#include "Renderer/WindowAdvanced.h"
#include "Renderer/Map/MapManager.h"

EEntity::EEntity(FEntityManager* InEntityManager)
	: IComponentManagerInterface(nullptr, InEntityManager->GetOwnerWindow())
	, EntityManagerOwner(InEntityManager)
	, DefaultRootComponent(nullptr)
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

	TickComponents(DeltaTime);
}

void EEntity::Render()
{
}

void EEntity::ReceiveRender()
{
	Render();

	RenderComponents();
}

void EEntity::SetRootComponent(UComponent* NewComponent)
{
	DefaultRootComponent = NewComponent;
}

UComponent* EEntity::GetRootComponent()
{
	return DefaultRootComponent;
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

FWindowAdvanced* EEntity::GetWindowAdvanced() const
{
	return reinterpret_cast<FWindowAdvanced*>(GetWindow());
}

FMap* EEntity::GetCurrentMap() const
{
	return GetWindow()->GetMapManager()->GetCurrentMap();
}

FGameModeManager* EEntity::GetGameModeManager() const
{
	return GetWindowAdvanced()->GetGameModeManager();
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

void EEntity::OnComponentCreated(const std::string& ComponentName, UComponent* NewComponent)
{
	IComponentManagerInterface::OnComponentCreated(ComponentName, NewComponent);

	if (DefaultRootComponent == nullptr)
	{
		DefaultRootComponent = NewComponent;
	}
}
