// Created by Przemys³aw Wiewióra 2023

#pragma once

#include "CoreMinimal.h"
#include "AssetBase.h"

class FTextureAsset;

enum FMapIndex : int8_t
{
	INDEX_INCORRECT = -1
};

namespace FMapFilesExtensions
{
	inline static const std::string PrimaryMapFileExtension = "amap";
	inline static const std::string MapDataFileExtension = "amapdata";
	inline static const CArray<std::string> AssetDirectoryNames = { "Assets", "assets" };
};
struct FMapSubAssetSettings
{
	/** Index to match texture to map */
	int AssetIndex;

	/** Collision index, currently 0 and 1 supported */
	int Collision;

	/** Asset pointer */
	std::shared_ptr<FTextureAsset> TextureAssetPtr;
};

struct FMapRow
{
	CArray<int> Array;
};

/**
 * For loading storing and using font.
 */
class FMapAsset : public FAssetBase
{
public:
	FMapAsset(const std::string& InAssetName, const std::string& InAssetPath);
	virtual ~FMapAsset() override;

	void SetMapManager(FMapManager* InMapManager);

	void LoadMap();
	void UnLoadMap();

	bool IsLoaded() const;

	void Draw();

protected:
	bool bIsLoaded;

	/** Primary map file describing map look */
	std::string MapNameFilePath;
	/** Path for file describing Map assets */
	std::string MapDataFilePath;
	/** Path for map textures */
	std::string MapAssetsDirPath;

	/** Each string is line from MapNameFilePath */
	CArray<std::string> MapLines;

	CArray<FMapSubAssetSettings> MapSubAssetSettingsArray;

	/** Array with tiles as ints */
	CArray<FMapRow> MapArray;

	FVector2D<int> AssetsTileSize;

	FMapManager* MapManager;

};
