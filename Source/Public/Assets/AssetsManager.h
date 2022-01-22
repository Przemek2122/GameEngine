// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"
#include "Containers/Map.h"
#include "Misc/Filesystem.h"

class FAssetBase;
class FFontAsset;
class FFont;

class FAssetsManager
{
	friend FEngine;
	
protected:
	FAssetsManager();
	virtual ~FAssetsManager();

public:
	/** Create asset by template type. */
	template<class TAssetType>
	void AddAsset(const std::string& InAssetName, const std::string& InAssetPath)
	{
		const std::string FullFilePath = GetFullFilePath(InAssetPath);
		
		if (FFilesystem::FileExists(FullFilePath))
		{
			AllAssetsMap.Emplace(InAssetName, std::make_shared<TAssetType>(InAssetName, FullFilePath));
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

	const FFontAsset& GetFont(const std::string& InFontAssetName, const int InFontSize);

protected:
	static std::string GetFullFilePath(const std::string& InPathRelative);

protected:
	/** All types of assets */
	CMap<std::string, std::shared_ptr<FAssetBase>> AllAssetsMap;
	
};
