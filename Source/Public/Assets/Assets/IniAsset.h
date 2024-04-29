// Created by Przemys³aw Wiewióra 2024

#pragma once

#include "AssetBase.h"

/**
 * For loading storing and using font.
 */
class FIniAsset : public FAssetBase
{
public:
	FIniAsset(const std::string& InAssetName, const std::string& InAssetPath);
	~FIniAsset() override;

	/** Begin FAssetBase */
	EAssetType GetAssetType() const override;
	/** End FAssetBase */

};
