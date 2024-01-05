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
	FMapManager();
	~FMapManager();

	void LoadMap(const std::string& Name);
	void UnLoadMap(const std::string& Name);

	void CacheAvailableMaps();
	CArray<std::string> GetAvailableMaps() const;

protected:
	CArray<std::string> AvailableMaps;
	CArray<FMapAsset*> MapAssets;

};
