// Created by Przemys³aw Wiewióra 2023

#pragma once

#include "CoreMinimal.h"
#include "AssetBase.h"

namespace FMapFilesExtensions
{
	inline static const std::string PrimaryMapFileExtension = "umap";
	inline static const std::string MapDataFileExtension = "amapdata";
	inline static const CArray<std::string> AssetDirectoryNames = { "Assets", "assets" };
};

/**
 * For loading storing and using font.
 */
class FMapAsset : public FAssetBase
{
public:
	FMapAsset(const std::string& InAssetName, const std::string& InAssetPath);
	virtual ~FMapAsset() override;

	void LoadMap();
	void UnLoadMap();

protected:
	std::string MapNameFilePath;
	std::string MapDataFilePath;
	std::string MapAssetsDirPath;


};
