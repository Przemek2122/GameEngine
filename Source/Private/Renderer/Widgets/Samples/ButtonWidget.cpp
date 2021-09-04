// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Renderer/Widgets/Samples/ButtonWidget.h"
#include "FunctorLambda.h"

FButtonWidget::FButtonWidget(IWidgetManagementInterface* InWidgetManagementInterface, const std::string& InWidgetName, const int InWidgetOrder)
	: FInteractionBaseWidget(InWidgetManagementInterface, InWidgetName, InWidgetOrder)
	, ButtonNormalColor(FColorRGBA::ColorGray())
	, ButtonHoverColor(FColorRGBA::ColorLightGray())
	, ButtonClickColor(FColorRGBA::ColorDarkGray())
{
	SetWidgetSize({ 200, 40 });

	ButtonRenderColor = ButtonNormalColor;

#if _DEBUG
	OnClickPress.BindLambda(
	[]
	{
		LOG_WARN("Button pressed!");
	});
	
	OnClickRelease.BindLambda(
	[]
	{
		LOG_WARN("Button released!");
	});
#endif
}

FButtonWidget::~FButtonWidget()
{
}

void FButtonWidget::Tick()
{
	Super::Tick();
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
