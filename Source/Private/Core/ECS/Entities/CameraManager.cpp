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
}

void ECameraManager::RegisterInput()
{
	FEventHandler* EventHandler = GEngine->GetEventHandler();

	if (EventHandler != nullptr)
	{
		EventHandler->MouseDelegates.GetMouseDelegateByName("Move")->Delegate.BindObject(this, &ECameraManager::OnMouseMove);

		EventHandler->MouseDelegates.GetMouseDelegateByName("RightButton")->Delegate.BindObject(this, &ECameraManager::OnMouseRightClick);
	}
}

void ECameraManager::UnregisterInput()
{
	FEventHandler* EventHandler = GEngine->GetEventHandler();

	if (EventHandler != nullptr)
	{
		EventHandler->MouseDelegates.GetMouseDelegateByName("Move")->Delegate.UnBindObject(this, &ECameraManager::OnMouseMove);

		EventHandler->MouseDelegates.GetMouseDelegateByName("RightButton")->Delegate.UnBindObject(this, &ECameraManager::OnMouseRightClick);
	}
}

void ECameraManager::OnMouseMove(const FVector2D<int> CurrentMouseLocation, EInputState)
{
	if (bIsRightMouseButtonPressed)
	{
		if (WindowMapManager != nullptr)
		{
			const FVector2D<int> LocationChange = CurrentMouseLocation - LastMouseLocation;

			WindowMapManager->MoveMap(LocationChange);
		}
	}

	LastMouseLocation = CurrentMouseLocation;
}

void ECameraManager::OnMouseRightClick(const FVector2D<int> CurrentMouseLocation, const EInputState InputState)
{
	if (InputState == EInputState::PRESS)
	{
		bIsRightMouseButtonPressed = true;

		LastMouseLocation = CurrentMouseLocation;
	}
	else if (InputState == EInputState::RELEASE)
	{
		bIsRightMouseButtonPressed = false;
	}
}
