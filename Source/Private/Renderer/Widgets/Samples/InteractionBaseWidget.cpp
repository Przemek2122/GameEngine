// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Renderer/Widgets/Samples/InteractionBaseWidget.h"
#include "Input/EventHandler.h"
#include "Renderer/Widgets/WidgetInputManager.h"

FInteractionBaseWidget::FInteractionBaseWidget(IWidgetManagementInterface* InWidgetManagementInterface, const std::string& InWidgetName, const int InWidgetOrder)
	: FWidget(InWidgetManagementInterface, InWidgetName, InWidgetOrder)
	, ClickState(EClickState::NotClicked)
	, HoverState(EHoverState::None)
	, bIsInWidget(false)
	, bMouseEnteredWidget(false)
{
}

FInteractionBaseWidget::~FInteractionBaseWidget()
{
}

void FInteractionBaseWidget::OnMouseMove(FVector2D<int> InMousePosition, EInputState InputState)
{
	const FVector2D<int> Location = GetWidgetLocation(EWidgetOrientation::Absolute);
	const FVector2D<int> Size = GetWidgetSize();

	bIsInWidget = false;
	
	if (InMousePosition.X	>	Location.X
	&&	InMousePosition.X	<	Location.X + Size.X
	&&	InMousePosition.Y	>	Location.Y
	&&	InMousePosition.Y	<	Location.Y + Size.Y )
	{
		bIsInWidget = true;
	}

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
}

void FInteractionBaseWidget::NativeRelease()
{
}

void FInteractionBaseWidget::NativeReleaseOutsideWidget()
{
}

void FInteractionBaseWidget::NativeHover()
{
	if (ClickState == EClickState::Released)
	{
		ClickState = EClickState::NotClicked;
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
