// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Assets/AssetsManager.h"

#include <memory>

#include "Assets/AssetBase.h"
#include "Assets/Font.h"
#include "Assets/FontAsset.h"

FAssetsManager::FAssetsManager()
{
}

FAssetsManager::~FAssetsManager()
{
	AllAssetsMap.Clear();
}

void FAssetsManager::RemoveAsset(const std::string& InAssetName)
{
	AllAssetsMap.Remove(InAssetName);
}

std::_Ptr_base<FAssetBase>::element_type* FAssetsManager::GetAsset(const std::string& InAssetName) const
{
	if (AllAssetsMap.ContainsKey(InAssetName))
	{	
		// @TODO dangling pointer
		return AllAssetsMap.At(InAssetName).get();
	}

	return nullptr;
}

std::_Ptr_base<FFont>::element_type* FAssetsManager::GetFont(const std::string& InFontAssetName, const int InFontSize)
{
	const std::string FontNameFull = InFontAssetName + "_" + std::to_string(InFontSize);
	
	auto* Font = TryFindFont(FontNameFull);

	if (Font != nullptr)
	{
		// Return font from map.
		return Font;
	}
	
	auto* FontAsset = dynamic_cast<std::_Ptr_base<FFontAsset>::element_type*>(GetAsset(InFontAssetName));

	// If we do not have font asset we can not create new size of Font
	if (FontAsset == nullptr)
	{
		return nullptr;
	}
	
	return MakeFont(FontAsset, FontNameFull, InFontSize);
}

std::_Ptr_base<FFont>::element_type* FAssetsManager::GetFont(FFontAsset* FontAsset, const int InFontSize)
{
	const std::string FontNameFull = FontAsset->GetAssetName() + "_" + std::to_string(InFontSize);

	auto* const Font  = TryFindFont(FontNameFull);
	
	if (Font != nullptr)
	{
		return Font;
	}

	return MakeFont(FontAsset, FontNameFull, InFontSize);
}

std::_Ptr_base<FFont>::element_type* FAssetsManager::TryFindFont(const std::string& InFontName)
{
	if (FontsMap.ContainsKey(InFontName))
	{
		// Return found element
		return FontsMap[InFontName].get();
	}

	return nullptr;
}

std::_Ptr_base<FFont>::element_type* FAssetsManager::MakeFont(FFontAsset* FontAsset, const std::string& NewFontName, const int NewFontSize)
{
	if (FontAsset != nullptr)
	{
		const auto NewFontPtr = std::make_shared<FFont>(NewFontName, FontAsset, NewFontSize);
			
		FontsMap.Emplace(NewFontName, NewFontPtr);

		// @TODO This should be fixed
		// Pointers to stack memory should be avoided.
		// But it works for now
		return NewFontPtr.get();
	}

	return nullptr;
}

std::string FAssetsManager::GetFullFilePath(const std::string& InPathRelative)
{
	char* Slash = FFilesystem::GetPlatformSlash();
	
	return Engine->GetLaunchRelativePath() + Slash + FFilesystem::GetAssetDirName() + Slash + InPathRelative;
}
