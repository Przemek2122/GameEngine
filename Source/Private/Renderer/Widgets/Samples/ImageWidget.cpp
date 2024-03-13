// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Renderer/Widgets/Samples/ImageWidget.h"
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

void FImageWidget::Render()
{
	if (TextureAsset != nullptr)
	{
		GetRenderer()->DrawTexture(TextureAsset, GetWidgetLocation(), GetWidgetSize());
	}

	FWidget::Render();
}

void FImageWidget::SetImage(const std::string& InImageName)
{
	bool bHasTexture = false;

	FAssetsManager* AssetsManager = GEngine->GetAssetsManager();
	if (AssetsManager != nullptr)
	{
		if (AssetsManager->HasAsset<FTextureAsset>(InImageName, EAssetType::AT_TEXTURE))
		{
			TextureAsset = AssetsManager->GetAsset<FTextureAsset>(InImageName, EAssetType::AT_TEXTURE);
			if (TextureAsset != nullptr)
			{
				bHasTexture = true;
			}
		}
		else
		{
			TextureAsset = AssetsManager->CreateAssetFromRelativePath<FTextureAsset>(InImageName, "FakePath").get();
			if (TextureAsset != nullptr)
			{
				bHasTexture = true;
			}
		}
	}

	if (bHasTexture)
	{
		if (bScaleWidgetToImage)
		{
			ScaleWidgetToTextureSize();
		}
	}
	else
	{
		LOG_ERROR("Unable to find texture asset: " << InImageName);
	}
}

void FImageWidget::SetImage(const std::shared_ptr<FTextureAsset>& TexturePtr)
{
	if (TexturePtr != nullptr)
	{
		TextureAsset = TexturePtr.get();

		if (bScaleWidgetToImage)
		{
			ScaleWidgetToTextureSize();
		}
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
