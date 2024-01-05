// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"
#include "AssetBase.h"
#include "Assets/TypesForAssets/Texture.h"

/**
 * For loading storing and using font.
 */
class FTextureAsset : public FAssetBase
{
public:
	FTextureAsset(const std::string& InAssetName, const std::string& InAssetPath);
	~FTextureAsset();

	void PrepareTexture(SDL_Renderer* InRenderer);
	FTexture* GetTexture() const;

protected:
	FTexture* Texture;

};
