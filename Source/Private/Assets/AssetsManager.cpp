// Created by Przemys�aw Wiewi�ra 2020

#include "CoreEngine.h"
#include "Assets/AssetsManager.h"
#include "Assets/Assets/AssetBase.h"
#include <memory>

FAssetsManager::FAssetsManager()
	: AssetDirName("Assets")
	, MapsDirName("Maps")
	, FontsDirName("Fonts")
{
}

FAssetsManager::~FAssetsManager()
{
	for (auto& [AssetType, Assets] : AssetsByType)
	{
		Assets.AssetsMap.Clear();
	}

	AssetsByType.Clear();
}

void FAssetsManager::RemoveAsset(const std::string& InAssetName, const EAssetType OptionalAssetType)
{
	if (OptionalAssetType == EAssetType::AT_NONE)
	{
		for (std::pair<const EAssetType, FAssetsStructure>& ByType : AssetsByType)
		{
			ByType.second.AssetsMap.Remove(InAssetName);
		}
	}
	else
	{
		AssetsByType[OptionalAssetType].AssetsMap.Remove(InAssetName);
	}
}

std::shared_ptr<FAssetBase> FAssetsManager::GetAsset(const std::string& InAssetName, const EAssetType OptionalAssetType)
{
	// Search all assets
	if (OptionalAssetType == EAssetType::AT_NONE)
	{
		for (const std::pair<const EAssetType, FAssetsStructure>& ByType : AssetsByType)
		{
			if (ByType.second.AssetsMap.ContainsKey(InAssetName))
			{
				return ByType.second.AssetsMap.At(InAssetName);
			}
		}
	}
	// Search specified type
	else
	{
		if (AssetsByType[OptionalAssetType].AssetsMap.ContainsKey(InAssetName))
		{
			return AssetsByType[OptionalAssetType].AssetsMap.At(InAssetName);
		}
	}

	return nullptr;
}

CArray<std::string> FAssetsManager::GetFilesFromDirectory(const std::string& Directory) const
{
	return FFileSystem::GetDirectories(ConvertRelativeToFullPath(Directory), true);
}

std::string FAssetsManager::GetProjectLocation() const
{
	return GEngine->GetLaunchRelativePath();
}

std::string FAssetsManager::GetAssetDirName() const
{
	return AssetDirName;
}

char FAssetsManager::GetPlatformSlash() const
{
	return FFileSystem::GetPlatformSlash();
}

std::string FAssetsManager::GetAssetsPathRelative() const
{
	return GetAssetDirName();
}

std::string FAssetsManager::GetMapsPathRelative() const
{
	const char Slash = FFileSystem::GetPlatformSlash();

	return GetAssetsPathRelative() + Slash + MapsDirName;
}

std::string FAssetsManager::GetFontsPathRelative() const
{
	const char Slash = FFileSystem::GetPlatformSlash();

	return GetAssetsPathRelative() + Slash + FontsDirName;
}

std::string FAssetsManager::ConvertRelativeToFullPath(const std::string& InPathRelative) const
{
	const char Slash = FFileSystem::GetPlatformSlash();
	
	return GEngine->GetLaunchRelativePath() + Slash + InPathRelative;
}
