// Created by Przemys�aw Wiewi�ra 2020

#include "CoreEngine.h"
#include "ECS/Components/Debug/ArrowComponent.h"

#include "Assets/AssetsManagerHelpers.h"
#include "Assets/Assets/TextureAsset.h"
#include "Assets/Collection/EngineAssetsCollection.h"
#include "ECS/Components/ParentComponent.h"

UArrowComponent::UArrowComponent(IComponentManagerInterface* InComponentManagerInterface)
	: UComponent(InComponentManagerInterface)
	, bOnlyVisibleInDebug(false)
	, RootTransformComponent(nullptr)
	, ArrowTextureAsset(nullptr)
{
}

void UArrowComponent::BeginPlay()
{
	Super::BeginPlay();

	UParentComponent* RootComponentOfEntity = GetRootComponentOfEntity();
	if (RootComponentOfEntity != nullptr)
	{
		RootTransformComponent = RootComponentOfEntity;
	}

	const FAssetCollectionItem& ArrowCollectionItem = FEngineAssetsCollection::ArrowTransparent1;
	FTextureAsset* NewTextureAsset = FAssetsManagerHelpers::GetOrCreateAsset<FTextureAsset>(GEngine->GetAssetsManager(), GetOwnerWindow(), ArrowCollectionItem.GetAssetName(), ArrowCollectionItem.GetAssetPath(), EAssetType::AT_TEXTURE);
	if (NewTextureAsset != nullptr)
	{
		SetArrow(NewTextureAsset);
	}
	else
	{
		LOG_ERROR("Unable to find arrow texture.");
	}
}

void UArrowComponent::EndPlay()
{
	if (ArrowTextureAsset != nullptr)
	{
		ArrowTextureAsset->DecrementNumberOfReferences();
		ArrowTextureAsset = nullptr;
	}

	Super::EndPlay();
}

void UArrowComponent::Render()
{
	Super::Render();

	bool bShouldRenderArrow = false;

	if (IsOnlyVisibleInDebug())
	{
		if (IsDebug())
		{
			bShouldRenderArrow = true;
		}
	}
	else
	{
		bShouldRenderArrow = true;
	}

	if (bShouldRenderArrow)
	{
		RenderArrow();
	}
}

void UArrowComponent::SetOnlyVisibleInDebug(const bool bInOnlyVisibleInDebug)
{
	bOnlyVisibleInDebug = bInOnlyVisibleInDebug;
}

bool UArrowComponent::IsOnlyVisibleInDebug() const
{
	return bOnlyVisibleInDebug;
}

bool UArrowComponent::IsDebug() const
{
	bool bIsDebug = false;

#if _DEBUG
	bIsDebug = true;
#endif

	return bIsDebug;
}

void UArrowComponent::RenderArrow()
{
	if (ArrowTextureAsset != nullptr)
	{
		FRenderer* Renderer = GetOwnerWindow()->GetRenderer();

		static const FVector2D<int> ArrowPivotPoint = { 0, 0 };

		FRenderer::OverrideTextureColor(ArrowTextureAsset->GetTexture()->GetSDLTexture(), FColorRGBA::ColorRed());
		Renderer->DrawTextureAdvanced(ArrowTextureAsset, GetLocationCenter(), ArrowRenderSize, GetRotation() + 180, ArrowPivotPoint, SDL_FLIP_VERTICAL);
		FRenderer::OverrideTextureColorReset(ArrowTextureAsset->GetTexture()->GetSDLTexture());
	}
}

void UArrowComponent::SetArrow(FTextureAsset* NewTextureAsset)
{
	if (RootTransformComponent != nullptr)
	{
		if (NewTextureAsset != nullptr)
		{
			if (ArrowTextureAsset != nullptr)
			{
				ArrowTextureAsset->DecrementNumberOfReferences();
			}

			ArrowTextureAsset = NewTextureAsset;
			ArrowTextureAsset->IncrementNumberOfReferences();

			ArrowRenderSize = NewTextureAsset->GetSize() / 3;

			SetLocationRelative(RootTransformComponent->GetSize() / 2);
		}
	}
	else
	{
		LOG_ERROR("Mising root component. Did you forget to create one?");
	}
}
