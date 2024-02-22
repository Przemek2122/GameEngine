// See https://github.com/Przemek2122/GameEngine

#pragma once

#include "CoreMinimal.h"
#include "Assets/Assets/MapAsset.h"

/**
 * Class for map management
 */
class FMap
{
public:
	FMap(FMapAsset* InMapAsset, FMapManager* InMapManager);
	virtual ~FMap() = default;

	void Initialize();

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

	FMapAsset* GetMapAsset() const { return MapAsset.Get(); }

protected:
	/** Map asset */
	FAutoDeletePointer<FMapAsset> MapAsset;

	/** Pointer to owner */
	FMapManager* MapManager;

	bool bIsActive;

	/** Map data: tiles size, tiles location and assets for map */
	FMapData MapData;

};
