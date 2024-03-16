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

	/** Checks given location (assumes it's absolute) if it's inside of bounds */
	bool IsInBounds(const FVector2D<int>& Location) const;

	/** Move map */
	void AddMapRenderOffset(const FVector2D<int>& LocationChange);

	/** Get map render offset */
	FVector2D<int> GetMapRenderOffset() const;

	/** Delegate triggered each time when map is moved */
	FDelegate<void, FVector2D<int>>& GetMapLocationChangeDelegate();

	/** Changes tile at given @Location with given @MapAssetIndexToSet. */
	void ChangeTileAtLocation(const FVector2D<int>& Location, int MapAssetIndexToSet);

protected:
	/** Map data: tiles size, tiles location and assets for map */
	FMapData MapData;

	/** Map asset */
	FMapAsset* MapAsset;

	/** Pointer to owner */
	FMapManager* MapManager;

	/** This property is for moving map */
	FVector2D<int> MapRenderOffset;

	/** Camera manager entity for map movement */
	ECameraManager* CameraManagerEntity;

	/** MapLocationChangeDelegate for map location change - Send new offset each time it's called */
	FDelegate<void, FVector2D<int>> MapLocationChangeDelegate;

	/** Is map activated */
	bool bIsActive;

};
