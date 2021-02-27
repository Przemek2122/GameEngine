// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"
#include "InteractionBaseWidget.h"

class FButtonWidget : public FInteractionBaseWidget
{
public:
	FButtonWidget(IWidgetManagementInterface* InWidgetManagementInterface, const std::string& InWidgetName, const int InWidgetOrder = 0);
	virtual ~FButtonWidget() override;

	virtual void Tick() override;
	virtual void Render() override;

	/** Begin FInteractionBaseWidget */
	virtual void NativeHover() override;
	virtual void NativePress() override;
	virtual void NativeRelease() override;
	virtual void NativeReleaseOutsideWidget() override;
	virtual void NativeMouseEnterWidget() override;
	virtual void NativeMouseExitWidget() override;
	/** End FInteractionBaseWidget */

public:
	FDelegate<> OnHover;
	FDelegate<> OnClickPress;
	FDelegate<> OnClickRelease;

protected:
	FColorRGBA ButtonRenderColor;

	FColorRGBA ButtonNormalColor;
	FColorRGBA ButtonHoverColor;
	FColorRGBA ButtonClickColor;
	
};
