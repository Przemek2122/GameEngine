// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Renderer/Widgets/Samples/ImageWidget.h"

#include "Assets/AssetsManagerHelpers.h"
#include "Assets/Assets/TextureAsset.h"

FImageWidget::FImageWidget(IWidgetManagementInterface* InWidgetManagementInterface, const std::string& InWidgetName, const int InWidgetOrder)
	: FWidget(InWidgetManagementInterface, InWidgetName, InWidgetOrder)
	, bScaleWidgetToImage(false)
	, TextureAsset(nullptr)
{
}

void FImageWidget::Init()
{
	FWidget::Init();

	SetWidgetSize({ 40, 40 });
}

void FImageWidget::DeInit()
{
	if (TextureAsset != nullptr)
	{
		TextureAsset->DecrementNumberOfReferences();
	}

	FWidget::DeInit();
}

void FImageWidget::Render()
{
	if (TextureAsset != nullptr)
	{
		GetRenderer()->DrawTexture(TextureAsset, GetWidgetLocation(), GetWidgetSize());
	}

	FWidget::Render();
}

void FImageWidget::SetImage(const std::string& InImageName, const std::string& OptionalPath)
{
	FAssetsManager* AssetsManager = GEngine->GetAssetsManager();
	if (AssetsManager != nullptr)
	{
		FTextureAsset* TemporaryTextureAsset = FAssetsManagerHelpers::GetOrCreateAsset<FTextureAsset>(AssetsManager, InImageName, EAssetType::AT_TEXTURE, OptionalPath, GetOwnerWindow());

		if (TemporaryTextureAsset != nullptr)
		{
			SetImage(TemporaryTextureAsset);
		}
		else
		{
			LOG_ERROR("Unable to find texture asset: " << InImageName);
		}
	}
}

void FImageWidget::SetImage(const std::shared_ptr<FTextureAsset>& TexturePtr)
{
	if (TexturePtr != nullptr)
	{
		SetImage(TexturePtr.get());
	}
}

void FImageWidget::SetImage(FTextureAsset* NewTexture)
{
	if (NewTexture != nullptr)
	{
		// Decrement old one - potentialy freeing memory
		if (TextureAsset != nullptr)
		{
			TextureAsset->DecrementNumberOfReferences();
		}

		// Set new one
		TextureAsset = NewTexture;
		TextureAsset->IncrementNumberOfReferences();

		if (bScaleWidgetToImage)
		{
			ScaleWidgetToTextureSize();
		}
	}
	else
	{
		LOG_ERROR("Texture 'InAsset' is nullptr.");
	}
}

void FImageWidget::SetScaleWidgetToImage(const bool bInScaleWidgetToImage)
{
	bScaleWidgetToImage = bInScaleWidgetToImage;

	if (bScaleWidgetToImage && TextureAsset != nullptr)
	{
		ScaleWidgetToTextureSize();
	}
}

void FImageWidget::ScaleWidgetToTextureSize()
{
	const FVector2D<int> TextureSize = TextureAsset->GetSize();

	SetWidgetSize(TextureSize);
}
