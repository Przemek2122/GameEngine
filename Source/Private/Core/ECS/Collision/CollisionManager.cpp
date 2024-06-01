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
	// @TODO Optimize, find tiles by location instead of checking all of them

	for (FCollisionMeshRow* CollisionRow : CollisionRows)
	{
		for (FCollisionTile* CollisionTile : CollisionRow->CollisionTiles)
		{
			
		}
	}

	// After puting it inside we should find intersections with other colliders
}

void FCollisionManager::RemoveCollisionFromMesh(FCollisionBase* InCollision)
{
	// @TODO Optimize, find tiles by location instead of checking all of them

	// ...

	// After removing collision we should find previous intersections and call on end of intersections?
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

bool FCollisionManager::IsIntersecting(FCollisionBase* CollisionA, FCollisionBase* CollisionB)
{
	bool bIsIntersecting = false;

	if (CollisionA->GetCollisionType() == ECollisionType::Other || CollisionB->GetCollisionType() == ECollisionType::Other)
	{
		// Handle any custom collision types
		bIsIntersecting = IsIntersectingCustomTypes(CollisionA, CollisionB);
	}
	else
	{
		switch (CollisionA->GetCollisionType())
		{
			case ECollisionType::Circle:
			{
				switch (CollisionB->GetCollisionType())
				{
					case ECollisionType::Circle:
					{
						const FCircle& CircleDataA = dynamic_cast<FCircleCollision*>(CollisionA)->GetCircleCollisionData();
						const FCircle& CircleDataB = dynamic_cast<FCircleCollision*>(CollisionB)->GetCircleCollisionData();

						bIsIntersecting = FCollisionGlobals::CirclesIntersect(CircleDataA, CircleDataB);

						break;
					}
					case ECollisionType::Square:
					{
						const FCircle& CircleData = dynamic_cast<FCircleCollision*>(CollisionA)->GetCircleCollisionData();
						const FRectangleWithDiagonal& RectangleData = dynamic_cast<FSquareCollision*>(CollisionB)->GetSquareData();

						bIsIntersecting = FCollisionGlobals::CircleAndSquareIntersect(RectangleData, CircleData);

						break;
					}
					case ECollisionType::Other:
					{
						LOG_ERROR("ECollisionType::Other found (#Circle). Collision will not work in this case.");

						break;
					}
				}

				break;
			}
			case ECollisionType::Square:
			{
				switch (CollisionB->GetCollisionType())
				{
					case ECollisionType::Circle:
					{
						const FRectangleWithDiagonal& RectangleData = dynamic_cast<FSquareCollision*>(CollisionA)->GetSquareData();
						const FCircle& CircleData = dynamic_cast<FCircleCollision*>(CollisionB)->GetCircleCollisionData();

						bIsIntersecting = FCollisionGlobals::CircleAndSquareIntersect(RectangleData, CircleData);

						break;
					}
					case ECollisionType::Square:
					{
						const FRectangleWithDiagonal& RectangleDataA = dynamic_cast<FSquareCollision*>(CollisionA)->GetSquareData();
						const FRectangleWithDiagonal& RectangleDataB = dynamic_cast<FSquareCollision*>(CollisionB)->GetSquareData();

						bIsIntersecting = FCollisionGlobals::RectanglesIntersect(RectangleDataA, RectangleDataB);

						break;
					}
					case ECollisionType::Other:
					{
						LOG_ERROR("ECollisionType::Other found (#Square). Collision will not work in this case.");

						break;
					}
				}

				break;
			}
			case ECollisionType::Other:
			{
				LOG_ERROR("ECollisionType::Other found. Collision will not work in this case.");

				break;
			}
		}
	}

	return bIsIntersecting;
}

bool FCollisionManager::IsIntersectingCustomTypes(FCollisionBase* CollisionA, FCollisionBase* CollisionB)
{
	LOG_WARN("Detected unsupported collision type.");

	return false;
}

CArray<FCollisionTile*> FCollisionManager::GetTilesIntersectingRectangle(const FVector2D<int>& InLocation, const FVector2D<int>& InSize) const
{
	CArray<FCollisionTile*> OutTiles;

	if (InSize > CollisionTileSize)
	{
		LOG_WARN("Custom logic is required for Objects greater than single CollisionTile. #1");
	}



	return std::move(OutTiles);
}

CArray<FCollisionTile*> FCollisionManager::GetTilesIntersectingCircle(const FVector2D<int>& InLocation, const int InRadius) const
{
	CArray<FCollisionTile*> OutTiles;

	if (InRadius > static_cast<int>(CollisionTileSize.Magnitude()))
	{
		LOG_WARN("Custom logic is required for Objects greater than single CollisionTile. #2");
	}

	OutTiles.Push(new FCollisionTile());

	return std::move(OutTiles);
}

bool FCollisionGlobals::RectanglesIntersect(const FRectangleWithDiagonal& RectangleA, const FRectangleWithDiagonal& RectangleB)
{
	return !(RectangleA.GetPositionBottomRight().X <= RectangleB.GetPositionTopLeft().X ||	// RectangleA is left of RectangleB 
		RectangleB.GetPositionBottomRight().X <= RectangleA.GetPositionTopLeft().X ||		// RectangleB is left of RectangleA 
		RectangleA.GetPositionBottomRight().Y <= RectangleB.GetPositionTopLeft().Y ||		// RectangleA is above RectangleB 
		RectangleB.GetPositionBottomRight().Y <= RectangleA.GetPositionTopLeft().Y);		// RectangleB is above RectangleA 
}

bool FCollisionGlobals::CirclesIntersect(const FCircle& CircleA, const FCircle& CircleB)
{
	const int Distance = CircleA.GetLocation().DistanceTo(CircleB.GetLocation());
	const int SummaryRadius = CircleA.GetRadius() + CircleB.GetRadius();

	return (SummaryRadius < Distance);
}

bool FCollisionGlobals::CircleAndSquareIntersect(const FRectangleWithDiagonal& Rectangle, const FCircle& Circle)
{
	// Find the closest point on the rectangle to the circle's center 
	const int Closest_x = FMath::Max(Rectangle.GetPositionTopLeft().X, FMath::Min(Circle.GetLocation().X, Rectangle.GetPositionTopLeft().X + Rectangle.GetSize().X));
	const int Closest_y = FMath::Max(Rectangle.GetPositionTopLeft().Y, FMath::Min(Circle.GetLocation().Y, Rectangle.GetPositionTopLeft().Y + Rectangle.GetSize().Y));

	// Calculate the distance from this closest point to the circle's center 
	const int distance = FMath::Sqrt((Circle.GetLocation().X - Closest_x) ^ 2 + (Circle.GetLocation().Y - Closest_y) ^ 2);

	// Check if the distance is less than or equal to the radius 
	return (distance <= Circle.GetRadius());

	/*
	float RectMinX = std::min(Rectangle.Corner1.X, Rectangle.Corner2.X);
	float RectMaxX = std::max(Rectangle.Corner1.X, Rectangle.Corner2.X);
	float RectMinY = std::min(Rectangle.Corner1.Y, Rectangle.Corner2.Y);
	float RectMaxY = std::max(Rectangle.Corner1.Y, Rectangle.Corner2.Y);

	// Find the closest point on the rectangle to the circle's center 
	FVector2D ClosestPoint(
		std::max(RectMinX, std::min(Circle.Center.X, RectMaxX)),
		std::max(RectMinY, std::min(Circle.Center.Y, RectMaxY))
	);

	// Calculate the distance between the circle's center and this closest point 
	float DistanceX = Circle.Center.X - ClosestPoint.X;
	float DistanceY = Circle.Center.Y - ClosestPoint.Y;

	// If the distance is less than the circle's radius, an intersection occurs 
	float DistanceSquared = DistanceX * DistanceX + DistanceY * DistanceY;
	return DistanceSquared <= (Circle.Radius * Circle.Radius);
	*/
}
