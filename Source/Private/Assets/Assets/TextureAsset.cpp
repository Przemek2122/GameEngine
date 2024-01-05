// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Assets/Assets/TextureAsset.h"
#include "Assets/TypesForAssets/Texture.h"

FTextureAsset::FTextureAsset(const std::string& InAssetName, const std::string& InAssetPath)
	: FAssetBase(InAssetName, InAssetPath)
	, Texture(nullptr)
{
}

FTextureAsset::~FTextureAsset()
{
	delete Texture;
}

void FTextureAsset::PrepareTexture(SDL_Renderer* InRenderer)
{
	Texture = new FTexture(AssetPath, InRenderer);
}

FTexture* FTextureAsset::GetTexture() const
{
	return Texture;
}
