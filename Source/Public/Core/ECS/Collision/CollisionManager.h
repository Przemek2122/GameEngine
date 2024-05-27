// Created by Przemys³aw Wiewióra 2024

#pragma once

#include "CoreMinimal.h"
#include "ECS/SubSystems/SubSystemInstanceInterface.h"

class FCollisionBase;
class FSquareCollision;
class FCircleCollision;

struct FCollisionTile
{
	FVector2D<int> TileLocation;
	FVector2D<int> TileSize;

	/** Array with collision objects inside of tile */
	CArray<FCollisionBase*> CollisionObjects;
};

struct FCollisionTilesRow
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

	void RegisterCircleCollision(FCircleCollision* InCircleCollision);
	void UnRegisterCircleCollision(FCircleCollision* InCircleCollision);

	void RegisterSquareCollision(FSquareCollision* SquareCollision);
	void UnRegisterSquareCollision(FSquareCollision* SquareCollision);

protected:
	void BuildCollision();
	void CreateCollisionTiles(const FMap* CurrentMap);

	void UpdateLocationOfCollisionInTiles();
	void CheckCollisionInTiles();

private:
	/** Circle collision array */
	CArray<FCircleCollision*> CircleCollisionArray;

	/** Square collision array */
	CArray<FSquareCollision*> SquareCollisionArray;

	/** Collision tiles */
	CArray<FCollisionTilesRow*> CollisionRows;

	/** Collision of single tile */
	FVector2D<int> CollisionTileSize;

	/** Called when collision is created */
	FDelegateSafe<void> OnCollisionTilesCreated;
	
};
