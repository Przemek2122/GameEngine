// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "ECS/Component.h"

class UBaseTransformComponent;

/**
 * Component for displaying simple arrow
 */
class UArrowComponent : public UComponent
{
public:
	UArrowComponent(IComponentManagerInterface* InComponentManagerInterface);
	virtual ~UArrowComponent() override = default;

	/** Begin UBaseComponent */
	void BeginPlay() override;
	void EndPlay() override;
	void Render() override;
	/** End UBaseComponent */

	void SetOnlyVisibleInDebug(const bool bInOnlyVisibleInDebug);
	bool IsOnlyVisibleInDebug() const;

protected:
	bool IsDebug() const;

	void RenderArrow();

	void SetArrow(FTextureAsset* NewTextureAsset);

private:
	bool bOnlyVisibleInDebug;

	UBaseTransformComponent* RootTransformComponent;

	FTextureAsset* ArrowTextureAsset;

	FVector2D<int> ArrowRenderSize;

};