// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Assets/Assets/FontAsset.h"
#include "Assets/TypesForAssets/Font.h"

FFontAsset::FFontAsset(const std::string& InAssetName, const std::string& InAssetPath)
	: FAssetBase(InAssetName, InAssetPath)
{
}

FFontAsset::~FFontAsset()
{
	for (const std::pair<const int, FFont*>& FontPair : Fonts)
	{
		delete FontPair.second;
	}
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
