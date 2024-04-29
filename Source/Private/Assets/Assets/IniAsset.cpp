// Created by Przemys�aw Wiewi�ra 2024

#include "CoreEngine.h"
#include "Assets/Assets/IniAsset.h"

FIniAsset::FIniAsset(const std::string& InAssetName, const std::string& InAssetPath)
	: FAssetBase(InAssetName, InAssetPath)
{
}

FIniAsset::~FIniAsset()
{
}

EAssetType FIniAsset::GetAssetType() const
{
	return EAssetType::AT_INI;
}
