// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "ECS/Entities/CameraManager.h"

#include "Input/EventHandler.h"
#include "Renderer/Map/MapManager.h"

ECameraManager::ECameraManager(FEntityManager* InEntityManager)
	: EEntity(InEntityManager)
	, WindowMapManager(nullptr)
{
}

void ECameraManager::BeginPlay()
{
	EEntity::BeginPlay();

	FMapManager* MapManager = GetWindow()->GetMapManager();
	if (MapManager != nullptr)
	{
		WindowMapManager = MapManager;
	}

	RegisterInput();
}

void ECameraManager::EndPlay()
{
	EEntity::EndPlay();

	UnregisterInput();
}

void ECameraManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (WindowMapManager != nullptr)
	{
		WindowMapManager->SetMapRenderOffset(CameraLocation);
	}
}

void ECameraManager::RegisterInput()
{
	const FEventHandler* EventHandler = GEngine->GetEventHandler();

	if (EventHandler != nullptr)
	{
		EventHandler->MouseDelegates.Move->Delegate.BindObject(this, &ECameraManager::OnMouseMove);

		EventHandler->MouseDelegates.RightButton->Delegate.BindObject(this, &ECameraManager::OnMouseRightClick);
	}
}

void ECameraManager::UnregisterInput()
{
}

void ECameraManager::OnMouseMove(FVector2D<int> Location, EInputState)
{
	LOG_DEBUG(Location.ToString());
}

void ECameraManager::OnMouseRightClick(FVector2D<int> Location, EInputState)
{
}
