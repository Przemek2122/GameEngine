// Created by Przemys�aw Wiewi�ra 2020

#include "CoreEngine.h"
#include "ECS/Components/RenderComponent.h"
#include "ECS/Components/TransformComponent.h"
#include "Assets/Assets/TextureAsset.h"

URenderComponent::URenderComponent(IComponentManagerInterface* InComponentManagerInterface)
	: UComponent(InComponentManagerInterface)
	, TextureAsset(nullptr)
{
	TransformComponent = RequireComponent<UTransformComponent>();

	TransformComponent->OnLocationChanged.BindObject(this, &URenderComponent::OnLocationChanged);

	LocationCached = TransformComponent->GetLocationFinal();
}

URenderComponent::~URenderComponent()
{
	TransformComponent->OnLocationChanged.UnBindObject(this, &URenderComponent::OnLocationChanged);
}

void URenderComponent::EndPlay()
{
	UComponent::EndPlay();

	DecrementTextureIfPresent();
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

	FTextureAsset* TemporaryTexture = nullptr;

	FAssetsManager* AssetsManager = GEngine->GetAssetsManager();
	if (AssetsManager != nullptr)
	{
		if (AssetsManager->HasAsset<FTextureAsset>(InImageName, EAssetType::AT_TEXTURE))
		{
			TemporaryTexture = AssetsManager->GetAsset<FTextureAsset>(InImageName, EAssetType::AT_TEXTURE);

			if (TemporaryTexture != nullptr)
			{
				bHasTexture = true;
			}
		}
		else if (!OptionalPath.empty())
		{
			TemporaryTexture = AssetsManager->AddAsset<FTextureAsset>(InImageName, OptionalPath);

			if (TemporaryTexture != nullptr)
			{
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
		SetImage(TemporaryTexture);
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
		DecrementTextureIfPresent();
	}

	if (InAsset != nullptr)
	{
		TextureAsset = InAsset;

		if (!TextureAsset->IsTexturePrepared())
		{
			TextureAsset->PrepareTexture(GetOwnerWindow()->GetRenderer()->GetSDLRenderer());
		}

		SetImageSize(TextureAsset->GetSize());

		TextureAsset->IncrementNumberOfReferences();
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

void URenderComponent::OnLocationChanged(const FVector2D<int> InLocation)
{
	LocationCached = InLocation;
}

void URenderComponent::DecrementTextureIfPresent() const
{
	if (TextureAsset != nullptr)
	{
		TextureAsset->DecrementNumberOfReferences();
	}
}
