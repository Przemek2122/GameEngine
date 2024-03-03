// See https://github.com/Przemek2122/GameEngine

#pragma once

#include "CoreMinimal.h"

class FMap;
class FMapAsset;

/**
 * Manager for maps.
 * Responsible for loading maps and managing them.
 */
class FMapManager
{
public:
	FMapManager(FWindow* InWindow);
	~FMapManager();

	virtual void DrawMap();

	/** Load map asset */
	virtual FMapAsset* LoadMap(const std::string& Name);

	/** UnLoad map asset (destroy asset data) */
	virtual void UnLoadMap(const std::string& Name);
	/** UnLoad map asset (destroy asset data) */
	virtual void UnLoadMap(FMapAsset* MapAsset);

	virtual void UnloadAllMaps();

	/** Iterate over all maps to find this with given name. Inefficient. */
	static FMapAsset* GetMapByName(const std::string& Name);

	/** Sets map active in game. */
	void SetActiveGameMap(FMapAsset* MapAsset);
	/** Deactivates map */
	void DeactivateCurrentGameMap();

	void SetCurrentEditorMap(FMap* Map);
	void DeactivateCurrentEditorMap();

	virtual void CacheAvailableMaps();
	virtual CArray<std::string> GetAvailableMaps() const;

	FWindow* GetWindow() const { return Window; };

	bool IsMapAssetCurrentlyUsed(FMapAsset* MapAsset);

protected:
	FMap* CurrentMap;
	CArray<std::string> AvailableMaps;
	CArray<FMapAsset*> MapAssets;

	FWindow* Window;

};
