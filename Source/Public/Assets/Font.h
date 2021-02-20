// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"
#include "AssetBase.h"

enum class EFontLoadMethod
{
	Instant,
	Lazy
};

/**
 * For loading storing and using font.
 */
class FFont
{
public:
	explicit FFont(const std::string& InFontName, std::_Ptr_base<FFontAsset>::element_type* InFontAsset, const int InFontSize);
	virtual ~FFont();

	_NODISCARD TTF_Font* GetFont();
	_NODISCARD int GetFontSize() const;

	_NODISCARD EFontLoadMethod GetFontLoadMethod() const;
	_NODISCARD std::string GetFontName() const;
	_NODISCARD std::string GetFontAssetName() const;
	
protected:
	virtual void InitializeFont();
	virtual void DeInitializeFont();

	TTF_Font *Font;
	
	const std::string& FontName;
	std::_Ptr_base<FFontAsset>::element_type* FontAsset;
	int FontSize;

	EFontLoadMethod FontLoadMethod;
	
};
