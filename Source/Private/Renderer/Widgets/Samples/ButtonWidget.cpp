// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Renderer/Widgets/Samples/ButtonWidget.h"
#include "FunctorLambda.h"

#define BUTTON_WIDGET_TEST_ENABLED 0

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
#if _DEBUG && BUTTON_WIDGET_TEST_ENABLED
	OnClickPress.BindLambda(
	[this]
	{
		LOG_DEBUG("Button '" << GetName() << "' pressed!");
	});
	
	OnClickRelease.BindLambda(
	[this]
	{
		LOG_DEBUG("Button '" << GetName() << "' released!");
	});
#endif

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
	Super::NativeHover();

	OnHover.Execute();
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
