// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"
#include "InteractionBaseWidget.h"

class FButtonWidget : public FInteractionBaseWidget
{
public:
	FButtonWidget(IWidgetManagementInterface* InWidgetManagementInterface, const std::string& InWidgetName, const int InWidgetOrder = 0);
	virtual ~FButtonWidget() override = default;

	/** Begin FWidget */
	void Init() override;
	void Render() override;
	/** End FWidget */

	/** Begin FInteractionBaseWidget */
	void NativeHover() override;
	void NativePress() override;
	void NativeRelease() override;
	void NativeReleaseOutsideWidget() override;
	void NativeMouseEnterWidget() override;
	void NativeMouseExitWidget() override;
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
