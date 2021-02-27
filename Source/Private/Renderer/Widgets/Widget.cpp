// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Renderer/Widgets/Widget.h"

#include <Windows.h>

FWidget::FWidget(IWidgetManagementInterface* InWidgetManagementInterface, const std::string InWidgetName)
	: WidgetManagementInterface(InWidgetManagementInterface)
	, WidgetVisibility(EWidgetVisibility::Visible)
	, Anchor(EAnchor::None)
	, DefaultAnchor(EAnchor::Center)
	, WidgetName(std::move(InWidgetName))
	, WidgetOrder(0)
	, bWasRenderedThisFrame(false)
{
#if _DEBUG
	if (WidgetManagementInterface == nullptr)
	{
		ENSURE_VALID_MESSAGE(false, "Widget with no IWidgetManagementInterface should not exists! Please fix pointer.");
	}
#endif
	
	WidgetManagementInterface->RegisterWidget(this);

	SetAnchor(DefaultAnchor);
}

FWidget::~FWidget()
{
#if _DEBUG
	if (WidgetManagementInterface == nullptr)
	{
		ENSURE_VALID_MESSAGE(false, "Widget with no widget manager should not exists!");
	}
#endif
	
	WidgetManagementInterface->UnRegisterWidget(this);
}

void FWidget::ReceiveTick()
{
	// Call on all children
	TickWidgets();
	
	HandleInput();

	Tick();
}

void FWidget::ReceiveRender()
{
	Render();

	// Call on all children
	RenderWidgets();
}

void FWidget::HandleInput()
{
	
}

void FWidget::Tick()
{
	
}

void FWidget::Render()
{
	
}

FVector2D<int> FWidget::GetWidgetManagerOffset() const
{
	return GetWidgetLocationAbsolute();
}

FVector2D<int> FWidget::GetWidgetManagerSize() const
{
	return GetWidgetSize();
}

FWindow* FWidget::GetOwnerWindow() const
{
	return WidgetManagementInterface->GetOwnerWindow();
}

bool FWidget::ShouldBeRendered() const
{
	return (WidgetVisibility == EWidgetVisibility::Visible || WidgetVisibility == EWidgetVisibility::VisibleNotInteractive);
}

FWindow* FWidget::GetWindow() const
{
	return WidgetManagementInterface->GetOwnerWindow();
}

FRenderer* FWidget::GetRenderer() const
{
	return GetWindow()->GetRenderer();
}

FEventHandler* FWidget::GetEventHandler()
{
	return Engine->GetEventHandler();
}

void FWidget::SetWidgetVisibility(const EWidgetVisibility InWidgetVisibility)
{
	WidgetVisibility = InWidgetVisibility;
}

EWidgetVisibility FWidget::GetWidgetVisibility() const
{
	return WidgetVisibility;
}

std::string FWidget::GetName() const
{
	return WidgetName;
}

int FWidget::GetWidgetOrder() const
{
	return WidgetOrder;
}

void FWidget::SetWidgetOrder(const int InWidgetOrder)
{
	WidgetOrder = InWidgetOrder;
	
	OnWidgetOrderChanged();
}

void FWidget::OnWidgetOrderChanged()
{
	WidgetManagementInterface->ChangeWidgetOrder(this);
}

FVector2D<int> FWidget::GetWidgetLocationAbsolute() const
{
	return WidgetLocation;
}

void FWidget::SetWidgetLocationAbsolute(const FVector2D<int> InWidgetLocation)
{
	WidgetLocation = InWidgetLocation;
}

FVector2D<int> FWidget::GetWidgetLocationRelative() const
{
	return WidgetLocation - GetWidgetManagerOffset();
}

void FWidget::SetWidgetLocationRelative(const FVector2D<int> InWidgetLocation)
{
	WidgetLocation = WidgetManagementInterface->GetWidgetManagerOffset() + InWidgetLocation;
}

FVector2D<int> FWidget::GetWidgetSize() const
{
	return WidgetSize;
}

void FWidget::SetWidgetSize(const FVector2D<int> InWidgetSize, const bool bUpdateAnchor)
{
	WidgetSize = InWidgetSize;

	if (bUpdateAnchor)
	{
		UpdateAnchor();
	}
}

void FWidget::SetAnchor(EAnchor NewAnchor)
{
	if (Anchor != NewAnchor)
	{
		Anchor = NewAnchor;
		
		OnAnchorChanged(NewAnchor);
	}
}

EAnchor FWidget::GetAnchor() const
{
	return Anchor;
}

void FWidget::UpdateAnchor()
{
	OnAnchorChanged(GetAnchor());
}

void FWidget::OnAnchorChanged(EAnchor NewAnchor)
{
	switch (NewAnchor)
	{
	case EAnchor::None:
		{
			// This should be for internal use only.
			// Old Anchor location will be used.
			ENSURE_VALID(false);
		}
		break;
		
	case EAnchor::Center:
		{
			const FVector2D<int> ParentSize = GetManagementInterface()->GetWidgetManagerSize();
			const FVector2D<int> ThisWidgetSize = GetWidgetSize();
			
			FVector2D<int> RelativeCenter;

			RelativeCenter.X = (ParentSize.X - ThisWidgetSize.X) / 2;
			RelativeCenter.Y = (ParentSize.Y - ThisWidgetSize.Y) / 2;

			// @TODO Does not work
			
			SetWidgetLocationRelative(RelativeCenter);
		}
		break;
		
	case EAnchor::LeftTop: 
		break;
		
	case EAnchor::LeftBottom: 
		break;
		
	case EAnchor::RightTop: 
		break;
		
	case EAnchor::RightBottom: 
		break;
		
	case EAnchor::TopCenter: 
		break;
		
	case EAnchor::LeftCenter: 
		break;
		
	case EAnchor::BottomCenter: 
		break;
		
	case EAnchor::RightCenter: 
		break;
	}
}

IWidgetManagementInterface* FWidget::GetManagementInterface() const
{
#if _DEBUG
	if (WidgetManagementInterface == nullptr)
	{
		ENSURE_VALID_MESSAGE(false, "Requested FWidgetManager but it has not been created!");
	}
#endif
	
	return WidgetManagementInterface;
}
