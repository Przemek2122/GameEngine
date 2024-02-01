// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Renderer/Widgets/Samples/InteractionBaseWidget.h"
#include "Input/EventHandler.h"
#include "Renderer/Widgets/WidgetInputManager.h"

FInteractionBaseWidget::FInteractionBaseWidget(IWidgetManagementInterface* InWidgetManagementInterface, const std::string& InWidgetName, const int InWidgetOrder)
	: FWidget(InWidgetManagementInterface, InWidgetName, InWidgetOrder)
	, ClickState(EClickState::NotClicked)
	, HoverState(EHoverState::None)
	, bMouseEnteredWidget(false)
{
	FDelegate<void, FWidgetInputManager*> SetupDelegate;
	SetupDelegate.BindObject(this, &FInteractionBaseWidget::SetupInput);

	GetWindow()->GetWidgetInputManager()->Register(this, SetupDelegate);

	SetupDelegate.UnBindObject(this, &FInteractionBaseWidget::SetupInput);
}

void FInteractionBaseWidget::Init()
{
	FWidget::Init();
}

void FInteractionBaseWidget::SetupInput(FWidgetInputManager* WidgetInputManager)
{
	WidgetInputManager->OnMouseLeftButtonRelease.Get()->BindObject(this, &FInteractionBaseWidget::OnMouseLeftButtonRelease);
	WidgetInputManager->OnMouseMove.Get()->BindObject(this, &FInteractionBaseWidget::OnMouseMove);
}

bool FInteractionBaseWidget::OnMouseLeftButtonRelease(FVector2D<int> Location)
{
	LOG_INFO("OnMouseLeftButtonRelease");

	return true;
}

void FInteractionBaseWidget::OnMouseMove(FVector2D<int> MouseLocation)
{
	const FVector2D<int> Location = GetWidgetLocation(EWidgetOrientation::Absolute);
	const FVector2D<int> Size = GetWidgetSize();

	bool bIsInWidget = false;
	
	if ( MouseLocation.X	>	Location.X	
	&&	 MouseLocation.X	<	Location.X + Size.X
	&&	 MouseLocation.Y	>	Location.Y	
	&&	 MouseLocation.Y	<	Location.Y + Size.Y )
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
	/*
	const bool bWasInputPressDetected = GetClickPressInput();
	const bool bWasInputReleaseDetected = GetClickReleaseInput();
	
	if (bWasInputPressDetected)
	{
		if (ClickState == EClickState::NotClicked)
		{
			ClickState = EClickState::Pressed;

			NativePress();
		}
	}
	else if (bWasInputReleaseDetected)
	{
		if (ClickState == EClickState::Pressed)
		{
			ClickState = EClickState::Released;

			NativeRelease();
		}
	}
	else if (ClickState == EClickState::Released)
	{
		ClickState = EClickState::NotClicked;
	}
	*/
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
		ENSURE_VALID(false);
		break;
	case EHoverState::Entered:
		NativeMouseEnterWidget();
		break;
	case EHoverState::Exited:
		NativeMouseExitWidget();
		break;
	}
}

void FInteractionBaseWidget::OnLeftMouseButtonReleased(FVector2D<int> Location)
{
}

void FInteractionBaseWidget::OnRightMouseButtonReleased(FVector2D<int> Location)
{
}
