// Created by Przemys³aw Wiewióra 2024

#include "CoreEngine.h"
#include "ECS/Collision/CollisionManager.h"

#include "Renderer/Map/Map.h"
#include "Renderer/Map/MapManager.h"

FCollisionManager::FCollisionManager()
{
}

void FCollisionManager::InitializeSubSystem()
{
	ISubSystemInstanceInterface::InitializeSubSystem();

	FWindow* Window = dynamic_cast<FWindow*>(GetSubSystemParentInterface());
	if (Window != nullptr)
	{
		FMapManager* MapManager = Window->GetMapManager();
		if (MapManager != nullptr)
		{
			FMap* CurrentMap = MapManager->GetCurrentMap();
			if (CurrentMap != nullptr)
			{
				FVector2D<int> TilesNumber = CurrentMap->GetMapSizeInTiles();

				// Create mesh for collision
			}
		}
	}
}

void FCollisionManager::TickSubSystem()
{
	Super::TickSubSystem();

	CheckCircleCollision();
	CheckSquareCollision();
}

void FCollisionManager::RegisterCircleCollision(FCircleCollision* InCircleCollision)
{
	CircleCollisionArray.Push(InCircleCollision);
}

void FCollisionManager::UnRegisterCircleCollision(FCircleCollision* InCircleCollision)
{
	CircleCollisionArray.Remove(InCircleCollision);
}

void FCollisionManager::RegisterSquareCollision(FSquareCollision* SquareCollision)
{
	SquareCollisionArray.Push(SquareCollision);
}

void FCollisionManager::UnRegisterSquareCollision(FSquareCollision* SquareCollision)
{
	SquareCollisionArray.Remove(SquareCollision);
}

void FCollisionManager::CheckCircleCollision()
{
}

void FCollisionManager::CheckSquareCollision()
{
}
