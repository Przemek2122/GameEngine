// Created by Przemys�aw Wiewi�ra 2020

#include "CoreEngine.h"
#include "Assets/Assets/TextureAsset.h"
#include "Assets/TypesForAssets/Texture.h"

FTextureAsset::FTextureAsset(const std::string& InAssetName, const std::string& InAssetPath)
	: FAssetBase(InAssetName, InAssetPath)
	, Texture(nullptr)
{
	LOG_INFO("Texture created " << AssetName);
}

FTextureAsset::~FTextureAsset()
{
	delete Texture;

	LOG_INFO("Texture destroyed " << AssetName);
}

EAssetType FTextureAsset::GetAssetType() const
{
	return EAssetType::AT_TEXTURE;
}

void FTextureAsset::PrepareTexture(SDL_Renderer* InRenderer)
{
	Texture = new FTexture(AssetPath, InRenderer);
}

FTexture* FTextureAsset::GetTexture() const
{
	return Texture;
}
