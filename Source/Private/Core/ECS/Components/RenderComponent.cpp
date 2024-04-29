// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "ECS/Components/RenderComponent.h"

#include "Assets/AssetsManagerHelpers.h"
#include "Assets/Assets/TextureAsset.h"

URenderComponent::URenderComponent(IComponentManagerInterface* InComponentManagerInterface)
	: UComponent(InComponentManagerInterface)
	, TextureAsset(nullptr)
{
}

URenderComponent::~URenderComponent()
{
}

void URenderComponent::EndPlay()
{
	Super::EndPlay();

	if (TextureAsset != nullptr)
	{
		TextureAsset->DecrementNumberOfReferences();
		TextureAsset = nullptr;
	}
}

void URenderComponent::Render()
{
	Super::Render();

	if (TextureAsset != nullptr)
	{
		GetOwnerWindow()->GetRenderer()->DrawTexture(TextureAsset, GetLocation(), SizeCached);
	}
}

void URenderComponent::SetImage(const std::string& InImageName, const std::string& OptionalPath)
{
	bool bHasTexture = false;

	FAssetsManager* AssetsManager = GEngine->GetAssetsManager();
	if (AssetsManager != nullptr)
	{
		FTextureAsset* TemporaryTexture = FAssetsManagerHelpers::GetOrCreateAsset<FTextureAsset>(AssetsManager, GetOwnerWindow(), InImageName, OptionalPath, EAssetType::AT_TEXTURE);

		if (TemporaryTexture != nullptr)
		{
			SetImage(TemporaryTexture);
		}
		else
		{
			LOG_ERROR("Asset: '" << InImageName << "' not found. If you would like to load it instead use OptionalPath parameter in URenderComponent::SetImage");
		}
	}
}

void URenderComponent::SetImage(FTextureAsset* InAsset)
{
	if (InAsset != nullptr)
	{
		// Decrement old one - potentialy freeing memory
		if (TextureAsset != nullptr)
		{
			TextureAsset->DecrementNumberOfReferences();
		}

		// Set new one
		TextureAsset = InAsset;
		TextureAsset->IncrementNumberOfReferences();

		SetImageSize(TextureAsset->GetSize());
	}
	else
	{
		LOG_ERROR("Texture 'InAsset' is nullptr.");
	}
}

void URenderComponent::SetImageSize(const FVector2D<int>& InSize)
{
	SizeCached = InSize;
}
