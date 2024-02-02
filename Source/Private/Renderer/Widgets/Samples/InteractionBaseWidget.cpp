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
}

FInteractionBaseWidget::~FInteractionBaseWidget()
{
}

void FInteractionBaseWidget::Init()
{
	FWidget::Init();

	FDelegate<void, FWidgetInputManager*> SetupDelegate;
	SetupDelegate.BindObject(this, &FInteractionBaseWidget::SetupInput);

	WidgetInputManager = GetWindow()->GetWidgetInputManager();
	WidgetInputManager->Register(this, SetupDelegate);
}

void FInteractionBaseWidget::DeInit()
{
	FWidget::DeInit();

	// @TODO Fix hack, instead of register we use direct call what works fine but does not look good.
	/*
	FDelegate<void, FWidgetInputManager*> ClearDelegate;
	ClearDelegate.BindObject(this, &FInteractionBaseWidget::ClearInput);

	WidgetInputManager->UnRegister(this, ClearDelegate);
	*/
	WidgetInputManager->OnMouseLeftButtonPress.Get()->UnBindObject(this, &FInteractionBaseWidget::OnMouseLeftButtonPress);
	WidgetInputManager->OnMouseLeftButtonRelease.Get()->UnBindObject(this, &FInteractionBaseWidget::OnMouseLeftButtonRelease);
	WidgetInputManager->OnMouseMove.Get()->UnBindObject(this, &FInteractionBaseWidget::OnMouseMove);
}

void FInteractionBaseWidget::SetupInput(FWidgetInputManager* WidgetInputManager)
{
	WidgetInputManager->OnMouseLeftButtonPress.Get()->BindObject(this, &FInteractionBaseWidget::OnMouseLeftButtonPress);
	WidgetInputManager->OnMouseLeftButtonRelease.Get()->BindObject(this, &FInteractionBaseWidget::OnMouseLeftButtonRelease);
	WidgetInputManager->OnMouseMove.Get()->BindObject(this, &FInteractionBaseWidget::OnMouseMove);
}

void FInteractionBaseWidget::ClearInput(FWidgetInputManager* WidgetInputManager)
{
	WidgetInputManager->OnMouseLeftButtonPress.Get()->UnBindObject(this, &FInteractionBaseWidget::OnMouseLeftButtonPress);
	WidgetInputManager->OnMouseLeftButtonRelease.Get()->UnBindObject(this, &FInteractionBaseWidget::OnMouseLeftButtonRelease);
	WidgetInputManager->OnMouseMove.Get()->UnBindObject(this, &FInteractionBaseWidget::OnMouseMove);
}

bool FInteractionBaseWidget::OnMouseLeftButtonPress(FVector2D<int> Vector2D)
{
	if (ClickState == EClickState::NotClicked)
	{
		ClickState = EClickState::Pressed;

		NativePress();
	}

	return true;
}

bool FInteractionBaseWidget::OnMouseLeftButtonRelease(FVector2D<int> Location)
{
	if (ClickState == EClickState::Pressed)
	{
		ClickState = EClickState::Released;

		NativeRelease();
	}

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
