// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Assets/Font.h"

#include "Assets/FontAsset.h"

FFont::FFont(const std::string& InFontName, std::_Ptr_base<FFontAsset>::element_type* InFontAsset, const int InFontSize)
	: Font(nullptr)
	, FontName(InFontName)
	, FontAsset(InFontAsset)
	, FontSize(InFontSize)
	, FontLoadMethod(EFontLoadMethod::Lazy)
{
	if (FontLoadMethod == EFontLoadMethod::Instant)
	{
		InitializeFont();
	}
}

FFont::~FFont()
{
	DeInitializeFont();
}

TTF_Font* FFont::GetFont()
{
	if (Font == nullptr)
	{
		InitializeFont();
	}

	return Font;
}

int FFont::GetFontSize() const
{
	return FontSize;
}

EFontLoadMethod FFont::GetFontLoadMethod() const
{
	return FontLoadMethod;
}

std::string FFont::GetFontName() const
{
	return FontName;
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
