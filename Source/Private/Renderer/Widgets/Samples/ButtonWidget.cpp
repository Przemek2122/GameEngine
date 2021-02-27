// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Renderer/Widgets/Samples/ButtonWidget.h"
#include "FunctorLambda.h"

FButtonWidget::FButtonWidget(IWidgetManagementInterface* InWidgetManagementInterface, const std::string& InWidgetName)
	: FInteractionBaseWidget(InWidgetManagementInterface, InWidgetName)
	, ButtonColor(200, 33, 150)
{
	SetWidgetSize({ 200, 40 });

	OnClicked.BindLambda(
	[]
	{
		LOG_WARN("Button clicked!");
	});
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

	GetRenderer()->DrawRectangle(GetWidgetLocationAbsolute(), GetWidgetSize(), ButtonColor);
}

void FButtonWidget::NativeClick()
{
	OnClicked.Execute();
}
