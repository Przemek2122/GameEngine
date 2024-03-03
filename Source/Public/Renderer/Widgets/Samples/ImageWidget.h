// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "../Widget.h"

class FTextureAsset;

/**
 * Widget for displaying image
 */
class FImageWidget : public FWidget
{
public:
	FImageWidget(IWidgetManagementInterface* InWidgetManagementInterface, const std::string& InWidgetName);
	virtual ~FImageWidget() override;

	/** Call to change texture of widget */
	void SetImage(const std::string& InImageName);

protected:
	bool bScaleWidgetToContent;
	FTextureAsset* TextureAsset;

};

