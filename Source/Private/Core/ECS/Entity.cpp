// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "ECS/Entity.h"

#include "Engine/Logic/GameModeManager.h"
#include "Renderer/WindowAdvanced.h"
#include "Renderer/Map/MapManager.h"

EEntity::EEntity(FEntityManager* InEntityManager)
	: IComponentManagerInterface(nullptr, InEntityManager->GetOwnerWindow())
	, EntityManagerOwner(InEntityManager)
	, DefaultRootComponent(nullptr)
	, bWasBeginPlayCalled(false)
{
}

void EEntity::BeginPlay()
{
	for (auto& ComponentPair : ComponentsMap)
	{
		ComponentPair.second->BeginPlay();
	}

	RegisterInputInternal();

	SetupAiActions();

	bWasBeginPlayCalled = true;
	bShouldCallBeginPlayOnNewComponents = true;
}

void EEntity::EndPlay()
{
	UnRegisterInputInternal();
}

void EEntity::Tick(float DeltaTime)
{
	for (const std::shared_ptr<FAiTree>& TreeArray : AiTreeArray)
	{
		TreeArray->TickInternal();
	}
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

#if _DEBUG
	UParentComponent* RootComponent = dynamic_cast<UParentComponent*>(GetRootComponent());
	if (RootComponent != nullptr)
	{
		FRenderer* Renderer = GetWindow()->GetRenderer();

		FVector2D<int> DebugRectLocation = RootComponent->GetLocation() - FVector2D<int>(2, 2);
		FVector2D<int> DebugRectSize = { 4, 4 };

		Renderer->DrawRectangle(DebugRectLocation, DebugRectSize, FColorRGBA::ColorOrange());
	}
#endif
}

void EEntity::SetRootComponent(UBaseComponent* NewComponent)
{
	DefaultRootComponent = NewComponent;
}

UBaseComponent* EEntity::GetRootComponent() const
{
	return DefaultRootComponent;
}

UParentComponent* EEntity::GetParentComponent() const
{
	return dynamic_cast<UParentComponent*>(DefaultRootComponent);
}

void EEntity::RegisterInput(FEventHandler* InputHandler)
{
}

void EEntity::UnRegisterInput(FEventHandler* InputHandler)
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

FGameModeBase* EEntity::GetGameMode() const
{
	return GetGameModeManager()->GetCurrentGameMode();
}

void EEntity::RegisterInputInternal()
{
	FEventHandler* InputHandler = GEngine->GetEventHandler();

	RegisterInput(InputHandler);
}

void EEntity::UnRegisterInputInternal()
{
	FEventHandler* InputHandler = GEngine->GetEventHandler();

	UnRegisterInput(InputHandler);
}

void EEntity::SetupAiActions()
{
}

void EEntity::OnComponentCreated(const std::string& ComponentName, UBaseComponent* NewComponent)
{
	IComponentManagerInterface::OnComponentCreated(ComponentName, NewComponent);

	if (DefaultRootComponent == nullptr)
	{
		DefaultRootComponent = NewComponent;
	}
}
