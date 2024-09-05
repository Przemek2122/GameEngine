// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"
#include "InteractionBaseWidget.h"

enum class EHorizontalAlignMethod : Uint8
{
	AlignToFit,
	AlignOnlyIfNotFitting
};

class FButtonWidget : public FInteractionBaseWidget
{
public:
	FButtonWidget(IWidgetManagementInterface* InWidgetManagementInterface, const std::string& InWidgetName, const int InWidgetOrder = WIDGET_DEFINES_DEFAULT_ORDER);
	virtual ~FButtonWidget() override = default;

	/** Begin FWidget */
	void Init() override;
	void Render() override;
	/** End FWidget */

	/** IWidgetPositionInterface FWidget */
	void RebuildWidget() override;
	/** End IWidgetPositionInterface */
	
	/** Begin FInteractionBaseWidget */
	void NativeHover() override;
	void NativePress() override;
	void NativeRelease() override;
	void NativeReleaseOutsideWidget() override;
	void NativeMouseEnterWidget() override;
	void NativeMouseExitWidget() override;
	/** End FInteractionBaseWidget */

	void SetUseDefaultSize(const bool bInUseDefaultSize);

	void SetScaleHorizontally(const bool bInScaleHorizontally);

	FColorRGBA GetButtonRenderColor() const { return ButtonRenderColor; }
	FColorRGBA GetButtonNormalColor() const { return ButtonNormalColor; }
	FColorRGBA GetButtonHoverColor() const { return ButtonHoverColor; }
	FColorRGBA GetButtonClickColor() const { return ButtonClickColor; }

	void SetButtonRenderColor(const FColorRGBA& Color);
	void SetButtonNormalColor(const FColorRGBA& Color);
	void SetButtonHoverColor(const FColorRGBA& Color);
	void SetButtonClickColor(const FColorRGBA& Color);

	FDelegate<> OnHover;
	FDelegate<> OnClickPress;
	FDelegate<> OnClickRelease;

protected:
	FColorRGBA ButtonRenderColor;
	FColorRGBA ButtonNormalColor;
	FColorRGBA ButtonHoverColor;
	FColorRGBA ButtonClickColor;

	/** If true, default size will be set in init */
	bool bUseDefaultSize;

	/** Should scale horizontally to fit children? */
	bool bScaleHorizontally;

	EHorizontalAlignMethod HorizontalAlignMethod;
	
};
