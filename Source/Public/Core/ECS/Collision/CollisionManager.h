// Created by Przemys�aw Wiewi�ra 2024

#pragma once

#include "CoreMinimal.h"
#include "ECS/SubSystems/SubSystemInstanceInterface.h"

struct FCircle;
struct FRectangleWithDiagonal;
class FCollisionBase;
class FSquareCollision;
class FCircleCollision;

/** Single tile of specified size in specified location */
struct FCollisionTile
{
	FVector2D<int> TileLocation;
	FVector2D<int> TileSize;

	/** Array with collision objects inside of tile */
	CArray<FCollisionBase*> CollisionObjects;
};

/** Row of tiles */
struct FCollisionMeshRow
{
	/** Array of collision in single horizontal row. */
	CArray<FCollisionTile*> CollisionTiles;
};

/**
 * Collision manager
 * Collision is managed using tiles for collision detection of collidable objects in same tile.
 */
class FCollisionManager : public ISubSystemInstanceInterface
{
public:
	FCollisionManager();
	~FCollisionManager() override;

	/** Begin ISubSystemInstanceInterface */
	void InitializeSubSystem() override;
	void TickSubSystem() override;
	void RenderSubSystem() override;
	/** End ISubSystemInstanceInterface */

	void RegisterCollision(FCollisionBase* InCollision);
	void UnRegisterCollision(FCollisionBase* InCollision);
	void OnCollisionObjectMoved(FCollisionBase* InCollisionObject);

	bool IsDebugEnabled() const { return bIsDebugEnabled; }

	/** Adds map location offset */
	FVector2D<int> ConvertLocationToAbsolute(const FVector2D<int>& Relative) const;

	/** Remove map location offset */
	FVector2D<int> ConvertLocationToRelative(const FVector2D<int>& Absolute) const;

protected:
	void OnMapLocationChange(FVector2D<int> NewLocation);

	void BuildCollision();
	void CreateCollisionTiles();

	void OnCollisionCreated();

	void PutCollisionIntoMesh(FCollisionBase* InCollision);
	void RemoveCollisionFromMesh(FCollisionBase* InCollision);
	void UpdateCollisionOnMesh(FCollisionBase* InCollision);

	bool IsIntersecting(FCollisionBase* CollisionA, FCollisionBase* CollisionB);

	CArray<FCollisionTile*> GetTilesFromCollision(FCollisionBase* InCollision);

	CArray<FCollisionTile*> GetTilesIntersectingRectangle(const FVector2D<int>& InLocation, const FVector2D<int>& InSize) const;
	CArray<FCollisionTile*> GetTilesIntersectingCircle(const FVector2D<int>& InLocation, const int InRadius) const;

	/** Handle collision custom types */
	virtual bool IsIntersectingCustomTypes(FCollisionBase* CollisionA, FCollisionBase* CollisionB);

	/** Handle collision custom types */
	virtual CArray<FCollisionTile*> GetTilesIntersectingCustomType(FCollisionBase* Collision);

	void OnCollisionBegin(FCollisionBase* CollisionA, FCollisionBase* CollisionB);
	void OnCollisionEnd(FCollisionBase* InCollision);

private:
	/** Circle collision array */
	CArray<FCollisionBase*> AllCollisionArray;

	/** Collision tiles */
	CArray<FCollisionMeshRow*> CollisionRows;

	/** Collision waiting for collision mesh to be built */
	CArray<FCollisionBase*> CollisionWaitingForAddArray;

	/** Collision waiting for collision mesh to be built */
	CArray<FCollisionBase*> CollisionWaitingForRemovalArray;

	/** Collision of single tile */
	FVector2D<int> CollisionTileSize;

	/** Size of map in pixels for async work */
	FVector2D<int> MapSizeInPixelsCache;

	/** Map offset */
	FVector2D<int> CurrentMapOffset;

	/** Called when collision is created */
	FDelegateSafe<void> OnCollisionTilesCreated;

	/** True if collision tiles are ready */
	bool bIsCollisionReady;

	/** If true debug will be enabled on manager and components */
	bool bIsDebugEnabled;

};

class FCollisionGlobals
{
public:
	static bool RectanglesIntersect(const FCollisionManager* CollisionManager, const FRectangleWithDiagonal& RectangleA, const FRectangleWithDiagonal& RectangleB);
	static bool CirclesIntersect(const FCollisionManager* CollisionManager, const FCircle& CircleA, const FCircle& CircleB);
	static bool CircleAndSquareIntersect(const FCollisionManager* CollisionManager, const FRectangleWithDiagonal& Rectangle, const FCircle& Circle);

};
