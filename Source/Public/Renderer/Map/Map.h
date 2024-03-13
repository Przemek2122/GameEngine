// See https://github.com/Przemek2122/GameEngine

#pragma once

#include "CoreMinimal.h"
#include "Assets/Assets/MapAsset.h"

class ECameraManager;

/**
 * Class for map management
 */
class FMap
{
public:
	FMap(FMapAsset* InMapAsset, FMapManager* InMapManager);
	virtual ~FMap() = default;

	void Initialize();
	void DeInitialize();

	int GetMapWidth() const;
	int GetMapHeight() const;

	FVector2D<int> GetMapSizeInTiles() const;
	FVector2D<int> GetMapSizeInPixels() const;

	/** Function used for drawing a map */
	virtual void Draw();

	/** Function used for loading a map */
	virtual void Load();
	/** Function used for unloading a map */
	virtual void ClearData();
	/** Function used for saving a map */
	virtual void Save();

	/** Reads data from asset into this class from MapAsset memory */
	virtual void ReadAsset();
	/** Write data from this class into asset into MapAsset memory */
	virtual void WriteAsset();

	/** Map asset used to load / save this map */
	FMapAsset* GetMapAsset() const { return MapAsset; }

	void AddMapLocation(const FVector2D<int>& LocationChange);
	FVector2D<int> GetMapLocation() const;

	/** Scale of map */
	float GetScale() const { return Scale; }
	/** Change of map scale when zooming */
	float GetScaleJump() const { return ScaleJump; }

protected:
	/** Map asset */
	FMapAsset* MapAsset;

	/** Pointer to owner */
	FMapManager* MapManager;

	/** Is map activated */
	bool bIsActive;

	/** Map data: tiles size, tiles location and assets for map */
	FMapData MapData;

	/** Map scale */
	float Scale;

	/** Map jump scale - How fast to change scale when zooming etc */
	float ScaleJump;

	/** This property is for moving map */
	FVector2D<int> MapLocation;

	ECameraManager* CameraManagerEntity;

};
