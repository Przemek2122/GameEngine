// Created by Przemys³aw Wiewióra 2024

#include "CoreEngine.h"
#include "ECS/Collision/CollisionManager.h"

#include "ECS/Collision/CircleCollision.h"
#include "ECS/Collision/SquareCollision.h"
#include "ECS/Components/CollisionComponent.h"
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

			CollisionWaitingForAddArray.Clear();
		}

		if (!CollisionWaitingForRemovalArray.IsEmpty())
		{
			for (FCollisionBase* Collision : CollisionWaitingForRemovalArray)
			{
				RemoveCollisionFromMesh(Collision);
			}

			CollisionWaitingForRemovalArray.Clear();
		}

#if _DEBUG
		if (bIsDebugEnabled)
		{
			FRenderDelegate* RenderDelegate = GEngine->GetRenderDelegate();
			if (RenderDelegate != nullptr)
			{
				RenderDelegate->BindObject(this, &FCollisionManager::DrawDebugMesh);
			}
		}
#endif
	}
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
		AsyncWork.BindObject(this, &FCollisionManager::CreateCollisionTiles);

		FDelegateSafe<> MainThreadCallback;
		MainThreadCallback.BindObject(this, &FCollisionManager::OnCollisionCreated);

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

void FCollisionManager::OnCollisionCreated()
{
	OnCollisionTilesCreated.Execute();

	bIsCollisionReady = true;

	LOG_INFO("Collision map created.");
}

void FCollisionManager::PutCollisionIntoMesh(FCollisionBase* InCollision)
{
	InCollision->CurrentlyLocatedTiles = GetTilesFromCollision(InCollision);

	for (FCollisionTile* Tile : InCollision->CurrentlyLocatedTiles)
	{
		Tile->CollisionObjects.Push(InCollision);
	}

	// After putting it inside we should find intersections with other colliders
	for (FCollisionTile* Tile : InCollision->CurrentlyLocatedTiles)
	{
		// Skip single colliders
		if (Tile->CollisionObjects.Size() > 1)
		{
			for (FCollisionBase* TileCollisionA : Tile->CollisionObjects)
			{
				for (FCollisionBase* TileCollisionB : Tile->CollisionObjects)
				{
					// Skip self
					if (TileCollisionA != TileCollisionB)
					{
						const bool bIsIntersecting = IsIntersecting(TileCollisionA, TileCollisionB);
						if (bIsIntersecting)
						{
							LOG_INFO("Found intersection :)!");

							OnCollisionBegin(TileCollisionA, TileCollisionB);
						}
					}
				}
			}
		}
	}
}

void FCollisionManager::RemoveCollisionFromMesh(FCollisionBase* InCollision)
{
	OnCollisionEnd(InCollision);
}

void FCollisionManager::UpdateCollisionOnMesh(FCollisionBase* InCollision, const FVector2D<int>& LastLocation, const FVector2D<int>& CurrentLocation)
{
	const CArray<FCollisionTile*> NewTiles = GetTilesFromCollision(InCollision);
	const CArray<FCollisionTile*> PreviousTiles = InCollision->CurrentlyLocatedTiles;
	
	InCollision->CurrentlyLocatedTiles = NewTiles;

	for (FCollisionTile* Tiles : InCollision->CurrentlyLocatedTiles)
	{
		for (FCollisionBase* CollisionObject : Tiles->CollisionObjects)
		{
			if (CollisionObject != InCollision)
			{
				const bool bWasIntersecting = CollisionObject->OtherCollidersCurrentlyColliding.Contains(InCollision);
				const bool bIsCurrentlyIntersecting = IsIntersecting(InCollision, CollisionObject);

				if (bWasIntersecting && !bIsCurrentlyIntersecting)
				{
					OnCollisionEnd(InCollision);
				}
				else if (!bWasIntersecting && bIsCurrentlyIntersecting)
				{
					OnCollisionBegin(InCollision, CollisionObject);
				}
			}
		}
	}
}

void FCollisionManager::CheckCollisionInTiles()
{
	if (bIsCollisionReady)
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
						const FCircle& CircleDataA = dynamic_cast<FCircleCollision*>(CollisionA)->GetCircleData();
						const FCircle& CircleDataB = dynamic_cast<FCircleCollision*>(CollisionB)->GetCircleData();

						bIsIntersecting = FCollisionGlobals::CirclesIntersect(CircleDataA, CircleDataB);

						break;
					}
					case ECollisionType::Square:
					{
						const FCircle& CircleData = dynamic_cast<FCircleCollision*>(CollisionA)->GetCircleData();
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
						const FCircle& CircleData = dynamic_cast<FCircleCollision*>(CollisionB)->GetCircleData();

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

CArray<FCollisionTile*> FCollisionManager::GetTilesFromCollision(FCollisionBase* InCollision)
{
	CArray<FCollisionTile*> OutTiles;

	switch (InCollision->GetCollisionType())
	{
		case ECollisionType::Circle:
		{
			FCircleCollision* CircleCollision = dynamic_cast<FCircleCollision*>(InCollision);
			const FCircle& CircleCollisionData = CircleCollision->GetCircleData();
			OutTiles = GetTilesIntersectingCircle(CircleCollisionData.GetLocation(), CircleCollisionData.GetRadius());

			break;
		}
		case ECollisionType::Square:
		{
			FSquareCollision* SquareCollision = dynamic_cast<FSquareCollision*>(InCollision);
			const FRectangleWithDiagonal& FRectangleWithDiagonalData = SquareCollision->GetSquareData();
			OutTiles = GetTilesIntersectingRectangle(FRectangleWithDiagonalData.GetPositionTopLeft(), FRectangleWithDiagonalData.GetSize());

			break;
		}
		case ECollisionType::Other:
		{
			OutTiles = GetTilesIntersectingCustomType(InCollision);

			break;
		}
	}

	return OutTiles;
}

CArray<FCollisionTile*> FCollisionManager::GetTilesIntersectingRectangle(const FVector2D<int>& InLocation, const FVector2D<int>& InSize) const
{
	CArray<FCollisionTile*> OutTiles;

	if (InSize > CollisionTileSize)
	{
		LOG_WARN("Custom logic is required for Objects greater than single CollisionTile. #1");
	}

	// Find edge locations and add to @OutTiles
	CArray<FVector2D<int>> RectangleEdgeLocations;
	RectangleEdgeLocations.Push({ InLocation.X, InLocation.Y });
	RectangleEdgeLocations.Push({ InLocation.X + InSize.X, InLocation.Y });
	RectangleEdgeLocations.Push({ InLocation.X, InLocation.Y + InSize.Y });
	RectangleEdgeLocations.Push(InLocation + InSize);

	for (const FVector2D<int>& RectangleEdgeLocation : RectangleEdgeLocations)
	{
		const FVector2D<float> TileLocation = FVector2D<float>(RectangleEdgeLocation) / FVector2D<float>(CollisionTileSize);
		FVector2D<int> TileLocationInt;

		TileLocationInt.X = FMath::FloorToInt(TileLocation.X);
		TileLocationInt.Y = FMath::FloorToInt(TileLocation.Y);

		if (CollisionRows.IsValidIndex(TileLocationInt.X))
		{
			FCollisionMeshRow* Row = CollisionRows[TileLocationInt.X];
			if (Row->CollisionTiles.IsValidIndex(TileLocationInt.Y))
			{
				FCollisionTile* Tile = Row->CollisionTiles[TileLocationInt.Y];

				OutTiles.Push(Tile);
			}
		}
	}

	return OutTiles;
}

CArray<FCollisionTile*> FCollisionManager::GetTilesIntersectingCircle(const FVector2D<int>& InLocation, const int InRadius) const
{
	CArray<FCollisionTile*> OutTiles;

	if (InRadius > static_cast<int>(CollisionTileSize.Magnitude()))
	{
		LOG_WARN("Custom logic is required for Objects greater than single CollisionTile. #2");
	}

	// Create Rectangle of circle size to find tiles using rectangle function
	const FVector2D<int> RectangleTopLeft = InLocation - FVector2D<int>(InRadius, InRadius);
	const FVector2D<int> RectangleSize = { InRadius * 2 };

	OutTiles = GetTilesIntersectingRectangle(RectangleTopLeft, RectangleSize);

	return OutTiles;
}

bool FCollisionManager::IsIntersectingCustomTypes(FCollisionBase* CollisionA, FCollisionBase* CollisionB)
{
	LOG_WARN("Detected unsupported collision type.");

	return false;
}

CArray<FCollisionTile*> FCollisionManager::GetTilesIntersectingCustomType(FCollisionBase* Collision)
{
	return { };
}

void FCollisionManager::OnCollisionBegin(FCollisionBase* CollisionA, FCollisionBase* CollisionB)
{
	CollisionA->OtherCollidersCurrentlyColliding.Push(CollisionB);
	CollisionB->OtherCollidersCurrentlyColliding.Push(CollisionA);

	CollisionA->GetCollisionComponent()->OnCollisionBegin(CollisionB->GetCollisionComponent());
	CollisionB->GetCollisionComponent()->OnCollisionBegin(CollisionA->GetCollisionComponent());
}

void FCollisionManager::OnCollisionEnd(FCollisionBase* InCollision)
{
	for (FCollisionBase* OtherCollider : InCollision->OtherCollidersCurrentlyColliding)
	{
		// Before removing collision we should find previous intersections and call on end of intersections?
		InCollision->GetCollisionComponent()->OnCollisionEnd(OtherCollider->GetCollisionComponent());
		OtherCollider->GetCollisionComponent()->OnCollisionEnd(InCollision->GetCollisionComponent());

		OtherCollider->OtherCollidersCurrentlyColliding.Remove(InCollision);
	}

	InCollision->OtherCollidersCurrentlyColliding.Clear();
}

#if _DEBUG
void FCollisionManager::DrawDebugMesh()
{
	LOG_INFO("DrawDebugMesh call");
}
#endif

bool FCollisionGlobals::RectanglesIntersect(const FRectangleWithDiagonal& RectangleA, const FRectangleWithDiagonal& RectangleB)
{
	return !(	RectangleA.GetPositionBottomRight().X <= RectangleB.GetPositionTopLeft().X	||	// RectangleA is left of RectangleB 
				RectangleB.GetPositionBottomRight().X <= RectangleA.GetPositionTopLeft().X	||		// RectangleB is left of RectangleA 
				RectangleA.GetPositionBottomRight().Y <= RectangleB.GetPositionTopLeft().Y	||		// RectangleA is above RectangleB 
				RectangleB.GetPositionBottomRight().Y <= RectangleA.GetPositionTopLeft().Y	);		// RectangleB is above RectangleA 
}

bool FCollisionGlobals::CirclesIntersect(const FCircle& CircleA, const FCircle& CircleB)
{
	const int Distance = CircleA.GetLocation().DistanceTo(CircleB.GetLocation());
	const int SummaryRadius = CircleA.GetRadius() + CircleB.GetRadius();

	return (SummaryRadius > Distance);
}

bool FCollisionGlobals::CircleAndSquareIntersect(const FRectangleWithDiagonal& Rectangle, const FCircle& Circle)
{
	// Find the closest point to the circle within the rectangle 
	int ClosestX = std::max(Rectangle.GetPositionTopLeft().X, std::min(Circle.GetLocation().X, Rectangle.GetPositionBottomRight().X));
	int ClosestY = std::max(Rectangle.GetPositionTopLeft().Y, std::min(Circle.GetLocation().Y, Rectangle.GetPositionBottomRight().Y));

	// Calculate the distance between the circle's center and this closest point 
	int DistanceX = Circle.GetLocation().X - ClosestX;
	int DistanceY = Circle.GetLocation().Y - ClosestY;

	// If the distance is less than the circle's radius, there is an intersection 
	int DistanceSquared = (DistanceX * DistanceX) + (DistanceY * DistanceY);
	return DistanceSquared < (Circle.GetRadius() * Circle.GetRadius());
}
