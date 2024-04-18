// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "ECS/Components/ArrowComponent.h"
#include "ECS/Components/BaseTransformComponent.h"

UArrowComponent::UArrowComponent(IComponentManagerInterface* InComponentManagerInterface)
	: UComponent(InComponentManagerInterface)
	, bOnlyVisibleInDebug(false)
	, RootTransformComponent(nullptr)
{
}

void UArrowComponent::BeginPlay()
{
	UComponent::BeginPlay();

	UComponent* RootComponentOfEntity = GetRootComponentOfEntity();
	if (RootComponentOfEntity != nullptr)
	{
		UBaseTransformComponent* TemporaryComponent = dynamic_cast<UBaseTransformComponent*>(RootComponentOfEntity);
		if (TemporaryComponent != nullptr)
		{
			RootTransformComponent = TemporaryComponent;
		}
	}

	//GEngine->GetAssetsManager()->GetOrCreateAsset<FTextureAsset>()
}

void UArrowComponent::Render()
{
	UComponent::Render();

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
	FRenderer* Renderer = GetOwnerWindow()->GetRenderer();

	Renderer->DrawCircle(RootTransformComponent->GetLocationCenter(), 20);
}
