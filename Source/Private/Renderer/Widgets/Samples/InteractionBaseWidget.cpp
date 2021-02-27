// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Renderer/Widgets/Samples/InteractionBaseWidget.h"
#include "Input/EventHandler.h"

FInteractionBaseWidget::FInteractionBaseWidget(IWidgetManagementInterface* InWidgetManagementInterface, const std::string& InWidgetName)
	: FWidget(InWidgetManagementInterface, InWidgetName)
	, bWasClicked(false)
{
}

FInteractionBaseWidget::~FInteractionBaseWidget()
{
}

void FInteractionBaseWidget::HandleInput()
{
	Super::HandleInput();

	const FVector2D<int> MouseLocation = GetMouseLocation();
	
	if ( MouseLocation.X	>	WidgetLocation.X	
	&&	 MouseLocation.X	<	WidgetLocation.X + WidgetSize.X
	&&	 MouseLocation.Y	>	WidgetLocation.Y	
	&&	 MouseLocation.Y	<	WidgetLocation.Y + WidgetSize.Y )
	{
		NativeHover();
	}
}

void FInteractionBaseWidget::Tick()
{
	Super::Tick();
}

void FInteractionBaseWidget::Render()
{
	Super::Render();
}

FVector2D<int> FInteractionBaseWidget::GetMouseLocation()
{
	return GetEventHandler()->GetMouseLocationCurrent();
}

bool FInteractionBaseWidget::GetClickInput()
{
	return GetEventHandler()->GetPrimaryInput("M_LMB");
}

void FInteractionBaseWidget::NativeClick()
{
}

void FInteractionBaseWidget::NativeHover()
{
	const bool bWasInputClickDetected = GetClickInput();
	
	if (bWasInputClickDetected)
	{
		if (!bWasClicked)
		{
			NativeClick();
			
			bWasClicked = true;
		}
		else
		{
			bWasClicked = false;
		}
	}
}
