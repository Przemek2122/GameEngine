// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Assets/AssetsManager.h"
#include <memory>
#include "Assets/AssetBase.h"

FAssetsManager::FAssetsManager()
{
}

FAssetsManager::~FAssetsManager()
{
	AllAssetsMap.Clear();
}

void FAssetsManager::RemoveAsset(const std::string& InAssetName)
{
	AllAssetsMap.Remove(InAssetName);
}

std::shared_ptr<FAssetBase> FAssetsManager::GetAsset(const std::string& InAssetName) const
{
	if (AllAssetsMap.ContainsKey(InAssetName))
	{
		// @TODO dangling pointer
		return AllAssetsMap.At(InAssetName);
	}

	return nullptr;
}

std::string FAssetsManager::GetFullFilePath(const std::string& InPathRelative)
{
	char* Slash = FFilesystem::GetPlatformSlash();
	
	return Engine->GetLaunchRelativePath() + Slash + FFilesystem::GetAssetDirName() + Slash + InPathRelative;
}
