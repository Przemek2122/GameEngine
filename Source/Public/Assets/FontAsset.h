// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"
#include "AssetBase.h"

/**
 * For loading storing and using font.
 */
class FFontAsset : public FAssetBase
{
public:
	FFontAsset(const std::string& InAssetName, const std::string& InAssetPath);
	virtual ~FFontAsset() override;
	
};
