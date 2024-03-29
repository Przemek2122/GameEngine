// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"
#include "Assets/AssetBase.h"
#include "Containers/Map.h"
#include "Misc/Filesystem.h"

enum class EAssetType : Uint8;
class FAssetBase;
class FFontAsset;
class FFont;

struct FAssetsColection
{
	CMap<std::string, std::shared_ptr<FAssetBase>> AssetsMap;
};

/**
 * Storage class. Registers assets which can be accesed anywhere.
 * Can also help with search for assets.
 */
class FAssetsManager
{
	friend FEngine;
	
protected:
	FAssetsManager();
	virtual ~FAssetsManager();

public:
	/** Create asset by template type. */
	template<class TAssetType>
	std::shared_ptr<TAssetType> CreateAssetFromAbsolutePath(const std::string& InAssetName, const std::string& InAssetPath)
	{
		if (FFileSystem::File::Exists(InAssetPath) || FFileSystem::Directory::Exists(InAssetPath))
		{
			std::shared_ptr<TAssetType> Asset = std::make_shared<TAssetType>(InAssetName, InAssetPath);

			return Asset;
		}
		else
		{
			LOG_ERROR("Missing asset at absolute path: " << InAssetPath);
		}

		return std::shared_ptr<TAssetType>(nullptr);
	}

	/** Create asset by template type. */
	template<class TAssetType>
	std::shared_ptr<TAssetType> CreateAssetFromRelativePath(const std::string& InAssetName, const std::string& InAssetPath)
	{
		const std::string FullFilePath = ConvertRelativeToFullPath(InAssetPath);

		if (FFileSystem::File::Exists(FullFilePath) || FFileSystem::Directory::Exists(FullFilePath))
		{
			std::shared_ptr<TAssetType> Asset = std::make_shared<TAssetType>(InAssetName, FullFilePath);

			return Asset;
		}
		else
		{
			LOG_ERROR("Missing asset at relative path: " << FullFilePath);
		}

		return std::shared_ptr<TAssetType>(nullptr);
	}

	/** Create and ADD asset by template type. */
	template<class TAssetType>
	TAssetType* AddAsset(const std::string& InAssetName, const std::string& InAssetPath)
	{
		const std::string FullFilePath = ConvertRelativeToFullPath(InAssetPath);
		
		if (FFileSystem::File::Exists(FullFilePath) || FFileSystem::Directory::Exists(FullFilePath))
		{
			std::shared_ptr<TAssetType> Asset = CreateAssetFromRelativePath<TAssetType>(InAssetName, InAssetPath);

			if (Asset.get() != nullptr)
			{
				EAssetType AssetTypeKey = Asset.get()->GetAssetType();

				// Add type if does not exists
				if (!AssetsByType.HasKey(AssetTypeKey))
				{
					AssetsByType.Emplace(AssetTypeKey, FAssetsColection());
				}

				AssetsByType[AssetTypeKey].AssetsMap.Emplace(InAssetName, Asset);

				return Asset.get();
			}
			else
			{
				LOG_ERROR("Failed to create asset: " << InAssetName);
			}
		}
		else
		{
			LOG_ERROR("Asset does not exists with name '" << InAssetName << "' and path: '" << InAssetPath << "'.");
		}

		return nullptr;
	}
	
	/** Delete asset by name. */
	void RemoveAsset(const std::string& InAssetName, const EAssetType OptionalAssetType = EAssetType::AT_NONE);
	
	/** @returns Asset created using AddAsset(...) */
	_NODISCARD std::shared_ptr<FAssetBase> GetAsset(const std::string& InAssetName, const EAssetType OptionalAssetType = EAssetType::AT_NONE);

	/** @returns Asset created using AddAsset(...) */
	template<typename TAssetSubClass>
	_NODISCARD TAssetSubClass* GetAsset(const std::string& InAssetName, const EAssetType OptionalAssetType = EAssetType::AT_NONE)
	{
		return dynamic_cast<TAssetSubClass*>(GetAsset(InAssetName, OptionalAssetType).get());
	}

	template<typename TAssetSubClass>
	_NODISCARD bool HasAsset(const std::string& InAssetName, const EAssetType OptionalAssetType = EAssetType::AT_NONE)
	{
		if (OptionalAssetType == EAssetType::AT_NONE)
		{
			LOG_WARN("Using FAssetsManager::HasAsset with all assets. Do you really do not know what type of asset you want. This is inefficient.");

			for (const std::pair<const EAssetType, FAssetsColection>& AssetsColection : AssetsByType)
			{
				if (AssetsColection.second.AssetsMap.ContainsKey(InAssetName))
				{
					return true;
				}
			}
		}
		else if (AssetsByType.HasKey(OptionalAssetType))
		{
			if (AssetsByType[OptionalAssetType].AssetsMap.ContainsKey(InAssetName))
			{
				return true;
			}
		}

		return false;
	}

	CArray<std::string> GetFilesFromDirectory(const std::string& Directory) const;

	std::string GetProjectLocation() const;

	/** @returns 'Assets' directory name */
	std::string GetAssetDirName() const;

	char GetPlatformSlash() const;

	std::string GetAssetsPathRelative() const;
	std::string GetMapsPathRelative() const;
	std::string GetFontsPathRelative() const;

protected:
	std::string ConvertRelativeToFullPath(const std::string& InPathRelative) const;

protected:
	/** All types of assets sorted by type */
	CMap<EAssetType, FAssetsColection> AssetsByType;

	/** Assets generic directory */
	std::string AssetDirName;
	/** Maps directory */
	std::string MapsDirName;
	/** Fonts directory */
	std::string FontsDirName;

};
