// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Renderer/Widgets/Samples/InteractionBaseWidget.h"
#include "Input/EventHandler.h"

FInteractionBaseWidget::FInteractionBaseWidget(IWidgetManagementInterface* InWidgetManagementInterface, const std::string& InWidgetName, const int InWidgetOrder)
	: FWidget(InWidgetManagementInterface, InWidgetName, InWidgetOrder)
	, ClickState(EClickState::NotClicked)
	, HoverState(EHoverState::None)
	, bIsInWidget(false)
	, bMouseEnteredWidget(false)
{
	SetWidgetInteraction(EWidgetInteraction::Interactive);
}
void FInteractionBaseWidget::OnMouseMove(FVector2D<int> InMousePosition, EInputState InputState)
{
	CheckIfMouseIsInsideWidget();
}

bool FInteractionBaseWidget::OnMouseLeftClick(FVector2D<int> InMousePosition, EInputState InputState)
{
	if (bIsInWidget && IsInteractive())
	{
		if (ClickState == EClickState::NotClicked)
		{
			ClickState = EClickState::Pressed;

			NativePress();

			return true;
		}
		else if (ClickState == EClickState::Pressed)
		{
			ClickState = EClickState::Released;

			NativeRelease();

			return true;
		}
	}

	return false;
}

FVector2D<int> FInteractionBaseWidget::GetMouseLocation()
{
	return GetEventHandler()->GetMouseLocationCurrent();
}

void FInteractionBaseWidget::NativePress()
{
	OnClickPress.Execute();
}

void FInteractionBaseWidget::NativeRelease()
{
	OnClickRelease.Execute();

	CheckIfMouseIsInsideWidget();
}

void FInteractionBaseWidget::NativeReleaseOutsideWidget()
{
}

void FInteractionBaseWidget::NativeHover()
{
	if (ClickState == EClickState::Released)
	{
		ClickState = EClickState::NotClicked;

		OnHover.Execute();
	}
}

void FInteractionBaseWidget::NativeMouseEnterWidget()
{
	
}

void FInteractionBaseWidget::NativeMouseExitWidget()
{
	if (ClickState == EClickState::Pressed)
	{
		NativeReleaseOutsideWidget();

		ClickState = EClickState::NotClicked;
	}
}

void FInteractionBaseWidget::CheckIfMouseIsInsideWidget()
{
	const FVector2D<int> Location = GetWidgetLocation(EWidgetOrientation::Absolute);
	const FVector2D<int> Size = GetWidgetSize();

	const FVector2D<int> LastMouseLocation = GetMouseLocation();
	bIsInWidget = IsLocationInsideWidget(LastMouseLocation);

	if (bIsInWidget)
	{
		if (!bMouseEnteredWidget)
		{
			NativeMouseEnterWidget();

			bMouseEnteredWidget = true;
		}

		NativeHover();
	}
	else
	{
		if (bMouseEnteredWidget)
		{
			NativeMouseExitWidget();

			bMouseEnteredWidget = false;
		}
	}
}

void FInteractionBaseWidget::SetHoverState(EHoverState NewHoverState)
{
	if (HoverState != NewHoverState)
	{
		HoverState = NewHoverState;
		
		OnHoverStateChanged();
	}
}

EHoverState FInteractionBaseWidget::GetHoverState() const
{
	return HoverState;
}

void FInteractionBaseWidget::OnHoverStateChanged()
{
	switch (HoverState)
	{
		case EHoverState::None:
		{
			ENSURE_VALID(false);

			break;
		}
		case EHoverState::Entered:
		{
			NativeMouseEnterWidget();

			break;
		}
		case EHoverState::Exited:
		{
			NativeMouseExitWidget();

			break;
		}
	}
}

void FInteractionBaseWidget::OnLeftMouseButtonReleased(FVector2D<int> Location)
{
}

void FInteractionBaseWidget::OnRightMouseButtonReleased(FVector2D<int> Location)
{
}
