// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Assets/Assets/AssetBase.h"

FAssetBase::FAssetBase(std::string InAssetName, std::basic_string<char> InAssetPath)
	: AssetName(std::move(InAssetName))
	, AssetPath(std::move(InAssetPath))
	, NumberOfReferences(0)
{
}

EAssetType FAssetBase::GetAssetType() const
{
	return EAssetType::AT_BASE;
}

std::string FAssetBase::GetAssetName() const
{
	return AssetName;
}

std::string FAssetBase::GetAssetPath() const
{
	return AssetPath;
}

void FAssetBase::IncrementNumberOfReferences()
{
	NumberOfReferences++;
}

void FAssetBase::DecrementNumberOfReferences()
{
	NumberOfReferences--;

	OnNumberOfReferencesLowered();
}

int FAssetBase::GetNumberOfReferences() const
{
	return NumberOfReferences;
}

void FAssetBase::OnNumberOfReferencesLowered()
{
	if (NumberOfReferences <= 0)
	{
		ReleaseTexture();
	}
}

void FAssetBase::ReleaseTexture()
{
	GEngine->GetAssetsManager()->RemoveAsset(AssetName, GetAssetType());
}
