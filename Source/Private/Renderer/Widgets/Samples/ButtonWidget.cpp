// Created by Przemys�aw Wiewi�ra 2020

#include "CoreEngine.h"
#include "Renderer/Widgets/Samples/ButtonWidget.h"
#include "FunctorLambda.h"

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
	Super::Init();

	SetWidgetSize({ 200, 40 });

#if _DEBUG
	OnClickPress.BindLambda(
	[this]
	{
		LOG_WARN("Button '" << GetName() << "' pressed!");
	});
	
	OnClickRelease.BindLambda(
	[this]
	{
		LOG_WARN("Button '" << GetName() << "' released!");
	});
#endif
}

void FButtonWidget::Render()
{
	Super::Render();

	GetRenderer()->DrawRectangle(GetWidgetLocationAbsolute(), GetWidgetSize(), ButtonRenderColor);
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
