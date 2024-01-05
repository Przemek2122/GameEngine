// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"
#include "Containers/Map.h"
#include "Misc/Filesystem.h"

class FAssetBase;
class FFontAsset;
class FFont;

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
		if (FFilesystem::FileExists(InAssetPath) || FFilesystem::DirectoryExists(InAssetPath))
		{
			std::shared_ptr<TAssetType> Asset = std::make_shared<TAssetType>(InAssetName, InAssetPath);

			return Asset;
		}

		return std::shared_ptr<TAssetType>(nullptr);
	}

	/** Create asset by template type. */
	template<class TAssetType>
	std::shared_ptr<TAssetType> CreateAssetFromRelativePath(const std::string& InAssetName, const std::string& InAssetPath)
	{
		const std::string FullFilePath = GetFullFilePath(InAssetPath);

		if (FFilesystem::FileExists(FullFilePath) || FFilesystem::DirectoryExists(FullFilePath))
		{
			std::shared_ptr<TAssetType> Asset = std::make_shared<TAssetType>(InAssetName, FullFilePath);

			return Asset;
		}

		return std::shared_ptr<TAssetType>(nullptr);
	}

	/** Create and ADD asset by template type. */
	template<class TAssetType>
	void AddAsset(const std::string& InAssetName, const std::string& InAssetPath)
	{
		const std::string FullFilePath = GetFullFilePath(InAssetPath);
		
		if (FFilesystem::FileExists(FullFilePath) || FFilesystem::DirectoryExists(FullFilePath))
		{
			AllAssetsMap.Emplace(InAssetName, CreateAssetFromRelativePath<TAssetType>(InAssetName, InAssetPath));
		}
		else
		{
			// Tried to add asset which does not exists, see FullFilePath
			ENSURE_VALID(false);
		}
	}
	
	/** Delete asset by name. */
	void RemoveAsset(const std::string& InAssetName);
	
	/** @returns Asset created in AddAsset(...) */
	_NODISCARD std::shared_ptr<FAssetBase> GetAsset(const std::string& InAssetName) const;

	/** @returns Asset created in AddAsset(...) */
	template<typename TAssetSubClass>
	_NODISCARD TAssetSubClass* GetAsset(const std::string& InAssetName) const
	{
		return dynamic_cast<TAssetSubClass*>(GetAsset(InAssetName).get());
	}

	CArray<std::string> GetFilesFromDirectory(const std::string& Directory) const;

	std::string GetProjectLocation() const;

	/** @returns 'Assets' directory name */
	std::string GetAssetDirName() const;

	char* GetPlatformSlash() const;

	std::string GetAssetsPathRelative() const;
	std::string GetMapsPathRelative() const;
	std::string GetFontsPathRelative() const;

protected:
	std::string GetFullFilePath(const std::string& InPathRelative) const;

protected:
	/** All types of assets */
	CMap<std::string, std::shared_ptr<FAssetBase>> AllAssetsMap;

	/** Assets generic directory */
	std::string AssetDirName;
	/** Maps directory */
	std::string MapsDirName;
	/** Fonts directory */
	std::string FontsDirName;

};
