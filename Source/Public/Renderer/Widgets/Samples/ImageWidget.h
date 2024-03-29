// Created by Przemys�aw Wiewi�ra 2020

#pragma once

#include "../Widget.h"

class FTextureAsset;

/**
 * Widget for displaying image
 * Renders before child widgets and before any class which inherits from it.
 */
class FImageWidget : public FWidget
{
public:
	FImageWidget(IWidgetManagementInterface* InWidgetManagementInterface, const std::string& InWidgetName, const int InWidgetOrder = WIDGET_DEFINES_DEFAULT_ORDER);

	/** Begin FWidget */
	void Init() override;
	void Render() override;
	/** End FWidget */

	/** Call to change texture of widget */
	void SetImage(const std::string& InImageName);

	/** Call to change texture of widget but only if you already have texture. */
	void SetImage(const std::shared_ptr<FTextureAsset>& TexturePtr);

	/** Should size of widget be changed to size of image? */
	void SetScaleWidgetToImage(const bool bInScaleWidgetToImage);

	void ScaleWidgetToTextureSize();

protected:
	/** Should we change size of widget depending on image? */
	bool bScaleWidgetToImage;

	/** Texture which we will render */
	FTextureAsset* TextureAsset;

};

