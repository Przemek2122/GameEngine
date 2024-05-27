// Created by Przemys³aw Wiewióra 2024

#include "CoreEngine.h"
#include "ECS/Collision/CollisionManager.h"

#include "Renderer/Map/Map.h"
#include "Threads/ThreadsManager.h"

FCollisionManager::FCollisionManager()
	: CollisionTileSize(64, 64)
{
}

FCollisionManager::~FCollisionManager()
{
	for (FCollisionTilesRow* CollisionRow : CollisionRows)
	{
		for (FCollisionTile* CollisionTile : CollisionRow->CollisionTiles)
		{
			delete CollisionTile;
		}

		delete CollisionRow;
	}
}

void FCollisionManager::InitializeSubSystem()
{
	ISubSystemInstanceInterface::InitializeSubSystem();

	BuildCollision();
}

void FCollisionManager::TickSubSystem()
{
	Super::TickSubSystem();
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

void FCollisionManager::BuildCollision()
{
	FMap* CurrentMap = dynamic_cast<FMap*>(GetSubSystemParentInterface());
	if (CurrentMap != nullptr)
	{
		FDelegateSafe<> AsyncWork;
		AsyncWork.BindLambda([&, CurrentMap]()
			{
				LOG_INFO("Creating collision map...");

				// If map is present create collision
				CreateCollisionTiles(CurrentMap);

				LOG_INFO("Collision map created.");
			});

		FDelegateSafe<> MainThreadCallback;
		MainThreadCallback.BindLambda([&]()
			{
				OnCollisionTilesCreated.Execute();

				LOG_INFO("Mainthread call after Collision map created.");
			});

		GEngine->GetThreadsManager()->AddAsyncDelegate(AsyncWork, MainThreadCallback);
	}
}

void FCollisionManager::CreateCollisionTiles(const FMap* CurrentMap)
{
	const FVector2D<int> MapSizeInPixels = CurrentMap->GetMapSizeInPixels();
	const FVector2D<int> TargetNumberOfTiles = MapSizeInPixels / CollisionTileSize;

	FVector2D<int> CurrentTileIndex;
	// Vertical tiles
	for (; CurrentTileIndex.Y < TargetNumberOfTiles.Y; CurrentTileIndex.Y++)
	{
		// Create row for new tiles
		FCollisionTilesRow* CollisionTilesRow = new FCollisionTilesRow();

		// Reset on each loop iteration
		CurrentTileIndex.X = 0;

		// Horizontal tiles
		for (; CurrentTileIndex.X < TargetNumberOfTiles.X; CurrentTileIndex.X++)
		{
			FCollisionTile* CollisionTile = new FCollisionTile();

			CollisionTile->TileLocation = CurrentTileIndex * CollisionTileSize;
			CollisionTile->TileSize = CollisionTileSize;

			CollisionTilesRow->CollisionTiles.Push(CollisionTile);
		}

		CollisionRows.Push(CollisionTilesRow);
	}

	LOG_INFO("Created " << TargetNumberOfTiles.X * TargetNumberOfTiles.Y << " tiles.");
}

void FCollisionManager::UpdateLocationOfCollisionInTiles()
{
	for (FCollisionTilesRow* CollisionRow : CollisionRows)
	{
		for (FCollisionTile* CollisionTile : CollisionRow->CollisionTiles)
		{
			
		}
	}
}

void FCollisionManager::CheckCollisionInTiles()
{
	for (FCollisionTilesRow* CollisionRow : CollisionRows)
	{
		for (FCollisionTile* CollisionTile : CollisionRow->CollisionTiles)
		{
			if (CollisionTile->CollisionObjects.Size() > 1)
			{
				for (FCollisionBase* CollisionObject : CollisionTile->CollisionObjects)
				{
					
					
				}
			}
		}
	}
}
