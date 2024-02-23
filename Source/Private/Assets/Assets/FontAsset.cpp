// Created by Przemys�aw Wiewi�ra 2020

#include "CoreEngine.h"
#include "Assets/Assets/FontAsset.h"
#include "Assets/TypesForAssets/Font.h"

FFontAsset::FFontAsset(const std::string& InAssetName, const std::string& InAssetPath)
	: FAssetBase(InAssetName, InAssetPath)
{
#if ENGINE_MEMORY_ALLOCATION_DEBUG_ASSETS
	LOG_INFO("Created font: t" << AssetName);
#endif
}

FFontAsset::~FFontAsset()
{
	for (const std::pair<const int, FFont*>& FontPair : Fonts)
	{
		delete FontPair.second;
	}

#if ENGINE_MEMORY_ALLOCATION_DEBUG_ASSETS
	LOG_INFO("Destroyed font: t" << AssetName);
#endif
}

FFont* FFontAsset::GetFont(const int Size)
{
	if (!Fonts.ContainsKey(Size))
	{
		MakeFont(Size);
	}

	return Fonts.At(Size);
}

void FFontAsset::MakeFont(const int Size)
{
	Fonts.Emplace(Size, new FFont(this, Size));
}
