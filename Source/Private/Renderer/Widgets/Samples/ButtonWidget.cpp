// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Renderer/Widgets/Samples/ButtonWidget.h"

FButtonWidget::FButtonWidget(IWidgetManagementInterface* InWidgetManagementInterface, const std::string& InWidgetName, const int InWidgetOrder)
	: FInteractionBaseWidget(InWidgetManagementInterface, InWidgetName, InWidgetOrder)
	, ButtonRenderColor(FColorRGBA::ColorGray())
	, ButtonNormalColor(FColorRGBA::ColorGray())
	, ButtonHoverColor(FColorRGBA::ColorLightGray())
	, ButtonClickColor(FColorRGBA::ColorDarkGray())
{
}

void FButtonWidget::Init()
{
	SetWidgetSize({ 200, 40 });

	Super::Init();
}

void FButtonWidget::Render()
{
	Super::Render();

	GetRenderer()->DrawRectangle(GetWidgetLocation(EWidgetOrientation::Absolute), GetWidgetSize(), ButtonRenderColor);
}

void FButtonWidget::NativeHover()
{
	OnHover.Execute();

	Super::NativeHover();
}

void FButtonWidget::NativePress()
{
	Super::NativePress();
	
	ButtonRenderColor = ButtonClickColor;
	
	OnClickPress.Execute();
}

void FButtonWidget::NativeRelease()
{
	Super::NativeRelease();
	
	ButtonRenderColor = ButtonNormalColor;
	
	OnClickRelease.Execute();
}

void FButtonWidget::NativeReleaseOutsideWidget()
{
	Super::NativeReleaseOutsideWidget();
	
	ButtonRenderColor = ButtonNormalColor;
}

void FButtonWidget::NativeMouseEnterWidget()
{
	Super::NativeMouseEnterWidget();
	
	ButtonRenderColor = ButtonHoverColor;
}

void FButtonWidget::NativeMouseExitWidget()
{
	Super::NativeMouseExitWidget();
	
	ButtonRenderColor = ButtonNormalColor;
}

void FButtonWidget::SetButtonRenderColor(const FColorRGBA& Color)
{
	ButtonRenderColor = Color;
}

void FButtonWidget::SetButtonNormalColor(const FColorRGBA& Color)
{
	ButtonNormalColor = Color;
}

void FButtonWidget::SetButtonHoverColor(const FColorRGBA& Color)
{
	ButtonHoverColor = Color;
}

void FButtonWidget::SetButtonClickColor(const FColorRGBA& Color)
{
	ButtonClickColor = Color;
}
