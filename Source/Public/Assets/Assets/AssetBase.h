// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"

enum class EAssetType : uint8_t
{
	/** None type - Will be used for searching all assets. */
	AT_NONE = 0,
	/** Default type - Will be used if function GetAssetType is not overriden. */
	AT_BASE = 1,
	AT_TEXTURE,
	AT_FONT,
	AT_AUDIO,
	AT_MAP,
};

/**
 * Base class for any asset type files.
 */
class FAssetBase
{
	friend FEngine;
	
public:
	FAssetBase(std::string InAssetName, std::string InAssetPath);
	virtual ~FAssetBase() = default;

	virtual EAssetType GetAssetType() const;

	_NODISCARD virtual std::string GetAssetName() const;
	_NODISCARD virtual std::string GetAssetPath() const;

protected:
	std::string AssetName;
	std::string AssetPath;
	
};
