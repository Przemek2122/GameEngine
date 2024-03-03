// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Renderer/Widgets/Samples/ImageWidget.h"
#include "Assets/Assets/TextureAsset.h"

FImageWidget::FImageWidget(IWidgetManagementInterface* InWidgetManagementInterface, const std::string& InWidgetName)
	: FWidget(InWidgetManagementInterface, InWidgetName)
	, bScaleWidgetToContent(true)
	, TextureAsset(nullptr)
{
}

FImageWidget::~FImageWidget()
{
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
		
	}
	else
	{
		LOG_ERROR("Unable to find texture asset: " << InImageName);
	}
}
