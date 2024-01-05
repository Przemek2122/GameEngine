// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Assets/TypesForAssets/Font.h"

#include "Assets/Assets/FontAsset.h"

FFont::FFont(FFontAsset* InFontAsset, const int InFontSize)
	: Font(nullptr)
	, FontAsset(InFontAsset)
	, FontSize(InFontSize)
{
	FFont::InitializeFont();
}

FFont::~FFont()
{
	FFont::DeInitializeFont();
}

TTF_Font* FFont::GetFont() const
{
	return Font;
}

int FFont::GetFontSize() const
{
	return FontSize;
}

void FFont::Reinitialize()
{
	Font = nullptr;
}

std::string FFont::GetFontAssetName() const
{
	return FontAsset->GetAssetName();
}

void FFont::InitializeFont()
{
	Font = TTF_OpenFont(FontAsset->GetAssetPath().c_str(), FontSize);

	if(Font == nullptr) 
	{
	    LOG_ERROR("TTF_OpenFont: %s\n" << TTF_GetError());
	}
}

void FFont::DeInitializeFont()
{
	TTF_CloseFont(Font);
}
