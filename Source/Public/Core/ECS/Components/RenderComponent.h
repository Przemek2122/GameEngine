// Created by Przemys³aw Wiewióra 2020-2024

#pragma once

#include "ECS/Component.h"

class UTransformComponent;
/**
 * Component for handling transform of the entity
 */
class URenderComponent : public UComponent
{
public:
	URenderComponent(IComponentManagerInterface* InComponentManagerInterface);
	virtual ~URenderComponent() override = default;

	/** Begin UComponent */
	void Tick() override;
	void Render() override;
	/** End UComponent */

	/** Set image from given name. It will try to find asset. If it was not created it will try to use OptionalPath to load it. */
	void SetImage(const std::string& InImageName, const std::string& OptionalPath = "");

	/** Set image from given asset. */
	void SetImage(FTextureAsset* InAsset);

	/** Set size. @Note SetImage sets always size of image, so call it after SetImage */
	void SetImageSize(const FVector2D<int>& InSize);

protected:
	/** Image to render */
	FTextureAsset* TextureAsset;

	/** Transform component - Required for location */
	UTransformComponent* TransformComponent;

	FVector2D<int> LocationCached;
	FVector2D<int> SizeCached;

};
