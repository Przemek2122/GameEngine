// See https://github.com/Przemek2122/GameEngine

#pragma once

#include "CoreMinimal.h"

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

	virtual void LoadMap(const std::string& Name);
	virtual void UnLoadMap(const std::string& Name);

	virtual void CacheAvailableMaps();
	virtual CArray<std::string> GetAvailableMaps() const;

	FWindow* GetWindow() const { return Window; };

protected:
	FMapAsset* CurrentMapAsset;
	CArray<std::string> AvailableMaps;
	CArray<FMapAsset*> MapAssets;

	FWindow* Window;

};
