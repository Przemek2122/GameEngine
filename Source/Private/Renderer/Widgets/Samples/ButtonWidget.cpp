// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Renderer/Widgets/Samples/ButtonWidget.h"
#include "FunctorLambda.h"

FButtonWidget::FButtonWidget(FWidgetManager* InWidgetManager, const std::string& InWidgetName)
	: FInteractionBaseWidget(InWidgetManager, InWidgetName)
	, ButtonColor(200, 33, 150)
{
	WidgetLocation = { 50, 50 };
	WidgetSize = { 200, 40 };

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

	GetRenderer()->DrawRectangle(GetWidgetLocation(), GetWidgetSize(), ButtonColor);
}

void FButtonWidget::NativeClick()
{
	OnClicked.Execute();
}
