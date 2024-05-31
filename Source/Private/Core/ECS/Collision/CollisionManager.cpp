// Created by Przemys³aw Wiewióra 2024

#include "CoreEngine.h"
#include "ECS/Collision/CollisionManager.h"

#include "ECS/Collision/CircleCollision.h"
#include "ECS/Collision/SquareCollision.h"
#include "Renderer/Map/Map.h"
#include "Threads/ThreadsManager.h"

FCollisionManager::FCollisionManager()
	: CollisionTileSize(64, 64)
	, bIsCollisionReady(false)
	, bIsDebugEnabled(true)
{
}

FCollisionManager::~FCollisionManager()
{
	for (FCollisionMeshRow* CollisionRow : CollisionRows)
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

	if (bIsCollisionReady)
	{
		if (!CollisionWaitingForAddArray.IsEmpty())
		{
			for (FCollisionBase* Collision : CollisionWaitingForAddArray)
			{
				PutCollisionIntoMesh(Collision);
			}
		}

		if (!CollisionWaitingForRemovalArray.IsEmpty())
		{
			for (FCollisionBase* Collision : CollisionWaitingForRemovalArray)
			{
				RemoveCollisionFromMesh(Collision);
			}
		}
	}

#if _DEBUG
	if (bIsDebugEnabled)
	{
		// It would be nice to draw mesh but we are missing render
		// @TODO Add render thread?
	}
#endif
}

void FCollisionManager::RegisterCollision(FCollisionBase* InCollision)
{
	AllCollisionArray.Push(InCollision);

	if (bIsCollisionReady)
	{
		PutCollisionIntoMesh(InCollision);
	}
	else
	{
		CollisionWaitingForAddArray.Push(InCollision);
	}
}

void FCollisionManager::UnRegisterCollision(FCollisionBase* InCollision)
{
	AllCollisionArray.Remove(InCollision);

	if (bIsCollisionReady)
	{
		RemoveCollisionFromMesh(InCollision);
	}
	else
	{
		CollisionWaitingForRemovalArray.Push(InCollision);
	}
}

void FCollisionManager::OnCollisionObjectMoved(FCollisionBase* InCollisionObject, const FVector2D<int>& LastLocation, const FVector2D<int>& CurrentLocation)
{
	if (bIsCollisionReady)
	{
		UpdateCollisionOnMesh(InCollisionObject, LastLocation, CurrentLocation);
	}
}

void FCollisionManager::BuildCollision()
{
	FMap* CurrentMap = dynamic_cast<FMap*>(GetSubSystemParentInterface());
	if (CurrentMap != nullptr)
	{
		MapSizeInPixelsCache = CurrentMap->GetMapSizeInPixels();

		FDelegateSafe<> AsyncWork;
		AsyncWork.BindLambda([&, CurrentMap]()
		{
			LOG_INFO("Creating collision map...");

			// If map is present create collision
			CreateCollisionTiles();

			LOG_INFO("Collision map created.");
		});

		FDelegateSafe<> MainThreadCallback;
		MainThreadCallback.BindLambda([&]()
		{
			OnCollisionTilesCreated.Execute();

			bIsCollisionReady = true;

			LOG_INFO("Mainthread call after Collision map created.");
		});

		bIsCollisionReady = false;

		GEngine->GetThreadsManager()->AddAsyncDelegate(AsyncWork, MainThreadCallback);
	}
}

void FCollisionManager::CreateCollisionTiles()
{
	const FVector2D<int> TargetNumberOfTiles = MapSizeInPixelsCache / CollisionTileSize;

	FVector2D<int> CurrentTileIndex;
	// Vertical tiles
	for (; CurrentTileIndex.Y < TargetNumberOfTiles.Y; CurrentTileIndex.Y++)
	{
		// Create row for new tiles
		FCollisionMeshRow* CollisionTilesRow = new FCollisionMeshRow();

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

void FCollisionManager::PutCollisionIntoMesh(FCollisionBase* InCollision)
{
	if (FCircleCollision* CircleCollision = dynamic_cast<FCircleCollision*>(InCollision))
	{
		
	}
	else if (FSquareCollision* SquareCollision = dynamic_cast<FSquareCollision*>(InCollision))
	{

	}
	else
	{
		LOG_WARN("Found unsupported collision type");
	}
}

void FCollisionManager::RemoveCollisionFromMesh(FCollisionBase* InCollision)
{
	if (FCircleCollision* CircleCollision = dynamic_cast<FCircleCollision*>(InCollision))
	{

	}
	else if (FSquareCollision* SquareCollision = dynamic_cast<FSquareCollision*>(InCollision))
	{

	}
	else
	{
		LOG_WARN("Found unsupported collision type");
	}


}

void FCollisionManager::UpdateCollisionOnMesh(FCollisionBase* InCollision, const FVector2D<int>& LastLocation, const FVector2D<int>& CurrentLocation)
{


}

void FCollisionManager::CheckCollisionInTiles()
{
	for (FCollisionMeshRow* CollisionRow : CollisionRows)
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

CArray<FCollisionTile*> FCollisionManager::GetTilesIntersectingRect(const FVector2D<int>& InLocation, const FVector2D<int>& InSize) const
{
	CArray<FCollisionTile*> Tiles;



	return Tiles;
}

bool FCollisionGlobals::RectanglesIntersect(const FRectangleWithDiagonal& RectangleA, const FRectangleWithDiagonal& RectangleB)
{
	return !(RectangleA.GetPositionBottomRight().X <= RectangleB.GetPositionTopLeft().X ||	// RectangleA is left of RectangleB 
		RectangleB.GetPositionBottomRight().X <= RectangleA.GetPositionTopLeft().X ||		// RectangleB is left of RectangleA 
		RectangleA.GetPositionBottomRight().Y <= RectangleB.GetPositionTopLeft().Y ||		// RectangleA is above RectangleB 
		RectangleB.GetPositionBottomRight().Y <= RectangleA.GetPositionTopLeft().Y);		// RectangleB is above RectangleA 
}
