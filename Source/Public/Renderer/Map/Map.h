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
	FMap(FMapAsset* InMapAsset);
	virtual ~FMap() = default;

	/** Function used for drawing a map */
	virtual void Draw();

	/** Function used for loading a map */
	virtual void Load();
	/** Function used for unloading a map */
	virtual void ClearData();
	/** Function used for saving a map */
	virtual void Save();

protected:
	/** Map asset */
	FAutoDeletePointer<FMapAsset> MapAsset;

	bool bIsLoaded;

};
