// Created by Przemys³aw Wiewióra 2023

#pragma once

#include "CoreMinimal.h"
#include "AssetBase.h"
#include "Assets/Parser.h"

class FTextureAsset;

enum FMapIndex : int8_t
{
	INDEX_INCORRECT = -1
};

/** Namespace for map files extensions and possible asset directory names */
namespace FMapFilesExtensions
{
	inline static const std::string PrimaryMapFileExtension = "amap";
	inline static const std::string MapDataFileExtension = "amapdata";
	inline static const CArray<std::string> AssetDirectoryNames = { "Assets", "assets" };
}

/** Namespace with comments added when saving a map */
namespace FMapFileComments
{
	inline static const std::string MapAssetsFileCommentLine1 = "Comments";
	inline static const std::string MapAssetsFileCommentLine2 = "Map file";
	inline static const std::string MapAssetsFileCommentLine3 = "First number is asset number,";
	inline static const std::string MapAssetsFileCommentLine4 = "Second one is collision, where 0 is no collision and 1 means collision";
}

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

	/** Load assets from disk */
	void LoadMap();
	/** Clear all arrays from loaded files from FMapAsset::LoadMap */
	void ClearMapData();
	/** OVERRIDE File this map source. This will removed old map. Be carefull when calling */
	void SaveMapData();

	bool IsLoaded() const;

	void Draw();

protected:
	static FParser CreateMapFilesParser();

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
