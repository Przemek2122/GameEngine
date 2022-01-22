// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Assets/FontAsset.h"

#include "Assets/Font.h"

FFontAsset::FFontAsset(const std::string& InAssetName, const std::string& InAssetPath)
	: FAssetBase(InAssetName, InAssetPath)
{
}

TTF_Font* FFontAsset::GetFont(const int Size)
{
	if (Fonts.ContainsKey(Size))
	{
		return Fonts[Size]->GetFont();
	}
	else
	{
		const std::shared_ptr<FFont> NewFont = MakeFont(Size);

		Fonts.Emplace(Size, NewFont);

		return NewFont->GetFont();
	}
}

std::shared_ptr<FFont> FFontAsset::MakeFont(const int Size)
{
	std::shared_ptr<FFont> NewFontPtr = std::make_shared<FFont>(this, Size);

	return NewFontPtr;
}
