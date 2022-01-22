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
	virtual ~FFontAsset() override = default;
	
	_NODISCARD TTF_Font* GetFont(const int Size);

	std::shared_ptr<FFont> MakeFont(const int Size);

protected:
	/** Different font sizes */
	CMap<int, std::shared_ptr<FFont>> Fonts;

};
