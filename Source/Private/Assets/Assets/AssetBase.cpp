// Created by Przemys�aw Wiewi�ra 2020

#include "CoreEngine.h"
#include "Assets/Assets/AssetBase.h"

FAssetBase::FAssetBase(std::string InAssetName, std::basic_string<char> InAssetPath)
	: AssetName(std::move(InAssetName))
	, AssetPath(std::move(InAssetPath))
{
}

std::string FAssetBase::GetAssetName() const
{
	return AssetName;
}

std::string FAssetBase::GetAssetPath() const
{
	return AssetPath;
}
