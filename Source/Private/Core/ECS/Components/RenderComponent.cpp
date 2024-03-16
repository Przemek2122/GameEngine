// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "ECS/Components/RenderComponent.h"
#include "ECS/Components/TransformComponent.h"
#include "Assets/Assets/TextureAsset.h"

URenderComponent::URenderComponent(IComponentManagerInterface* InComponentManagerInterface)
	: UComponent(InComponentManagerInterface)
{
	TransformComponent = RequireComponent<UTransformComponent>();
}

void URenderComponent::Tick()
{
	Super::Tick();

	if (TransformComponent != nullptr)
	{
		LocationCached = TransformComponent->GetLocationFinal();
	}
}

void URenderComponent::Render()
{
	Super::Render();

	if (TextureAsset != nullptr)
	{
		GetOwnerWindow()->GetRenderer()->DrawTexture(TextureAsset, LocationCached, SizeCached);
	}
}

void URenderComponent::SetImage(const std::string& InImageName, const std::string& OptionalPath)
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
		else if (!OptionalPath.empty())
		{
			TextureAsset = AssetsManager->AddAsset<FTextureAsset>(InImageName, OptionalPath);

			if (TextureAsset != nullptr)
			{
				TextureAsset->PrepareTexture(GetOwnerWindow()->GetRenderer()->GetSDLRenderer());

				bHasTexture = true;
			}
		}
		else
		{
			LOG_ERROR("Asset: '" << InImageName << "' not found. If you would like to load it instead use OptionalPath parameter in URenderComponent::SetImage");
		}
	}

	if (bHasTexture)
	{
		SizeCached = TextureAsset->GetSize();
	}
	else
	{
		LOG_ERROR("Unable to find texture asset: " << InImageName);
	}
}

void URenderComponent::SetImage(FTextureAsset* InAsset)
{
	if (TextureAsset != nullptr)
	{
		TextureAsset = InAsset;

		SizeCached = TextureAsset->GetSize();
	}
	else
	{
		LOG_ERROR("Texture asset is nullptr");
	}
}

void URenderComponent::SetImageSize(const FVector2D<int>& InSize)
{
	SizeCached = InSize;
}
