// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Assets/FontAsset.h"

FFontAsset::FFontAsset(const std::string& InAssetName, const std::string& InAssetPath)
	: FAssetBase(InAssetName, InAssetPath)
{
}

FFontAsset::~FFontAsset()
{
}
