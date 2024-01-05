// Created by Przemys³aw Wiewióra 2023

#include "CoreEngine.h"
#include "Assets/Assets/MapAsset.h"

FMapAsset::FMapAsset(const std::string& InAssetName, const std::string& InAssetPath)
	: FAssetBase(InAssetName, InAssetPath)
{
}

FMapAsset::~FMapAsset()
{
}

void FMapAsset::LoadMap()
{
	if (FFilesystem::DirectoryExists(AssetPath))
	{
		const std::string SharedBeginning = AssetPath + Engine->GetAssetsManager()->GetPlatformSlash();
		const std::string SharedBeginningFiles = SharedBeginning + AssetName;

		MapNameFilePath = SharedBeginningFiles + '.' + FMapFilesExtensions::PrimaryMapFileExtension;
		MapDataFilePath = SharedBeginningFiles + '.' + FMapFilesExtensions::MapDataFileExtension;

		for (const std::string& AssetDirectoryName : FMapFilesExtensions::AssetDirectoryNames)
		{
			const std::string Path = SharedBeginning + AssetDirectoryName;

			if (FFilesystem::DirectoryExists(Path))
			{
				MapAssetsDirPath = Path;

				break;
			}
		}

		if (	FFilesystem::FileExists(MapNameFilePath) 
			&&	FFilesystem::FileExists(MapDataFilePath) 
			&&	FFilesystem::DirectoryExists(MapAssetsDirPath))
		{
			
		}
		else
		{
			LOG_ERROR("Missing map files.");
		}
	}
	else
	{
		LOG_ERROR("Missing directory for map.");
	}
}

void FMapAsset::UnLoadMap()
{
}
