// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Assets/Assets/TextureAsset.h"
#include "Assets/TypesForAssets/Texture.h"

FTextureAsset::FTextureAsset(const std::string& InAssetName, const std::string& InAssetPath)
	: FAssetBase(InAssetName, InAssetPath)
	, Texture(nullptr)
	, bIsTexturePrepared(false)
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

FVector2D<int> FTextureAsset::GetSize() const
{
	FVector2D<int> Size;

	SDL_QueryTexture(Texture->GetSDLTexture(), nullptr, nullptr, &Size.X, &Size.Y);

	return Size;
}

FTexture* FTextureAsset::GetTexture() const
{
	return Texture;
}

void FTextureAsset::PrepareTexture(SDL_Renderer* InRenderer)
{
	if (!bIsTexturePrepared)
	{
		Texture = new FTexture(AssetPath, InRenderer);

		bIsTexturePrepared = true;
	}
}

bool FTextureAsset::IsTexturePrepared() const
{
	return bIsTexturePrepared;
}
