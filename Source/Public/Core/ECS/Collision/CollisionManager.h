// Created by Przemys³aw Wiewióra 2024

#pragma once

#include "CoreMinimal.h"
#include "ECS/SubSystems/SubSystemInstanceInterface.h"

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
	/** End ISubSystemInstanceInterface */

	void RegisterCollision(FCollisionBase* InCollision);
	void UnRegisterCollision(FCollisionBase* InCollision);
	void OnCollisionObjectMoved(FCollisionBase* InCollisionObject);

protected:
	void BuildCollision();
	void CreateCollisionTiles(const FMap* CurrentMap);

	void PutCollisionIntoMesh(FCollisionBase* Base);
	void RemoveCollisionFromMesh(FCollisionBase* Base);

	void UpdateLocationOfCollisionInTiles();
	void CheckCollisionInTiles();

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

	/** Called when collision is created */
	FDelegateSafe<void> OnCollisionTilesCreated;

	/** True if collision tiles are ready */
	bool bIsCollisionReady;
	
};
