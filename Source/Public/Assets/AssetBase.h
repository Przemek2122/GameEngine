// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"

/**
 * Base class for any asset type files.
 */
class FAssetBase
{
	friend FEngine;
	
public:
	FAssetBase(const std::string& InAssetName, const std::string& InAssetPath);
	virtual ~FAssetBase();

	_NODISCARD virtual std::string GetAssetName() const;
	_NODISCARD virtual std::string GetAssetPath() const;

protected:
	std::string AssetName;
	std::string AssetPath;
	
};
