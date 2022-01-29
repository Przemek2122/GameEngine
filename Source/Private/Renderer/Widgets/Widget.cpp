// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Renderer/Widgets/Widget.h"

#include <Windows.h>

FWidget::FWidget(IWidgetManagementInterface* InWidgetManagementInterface, std::string InWidgetName, const int InWidgetOrder)
	: WidgetVisibility(EWidgetVisibility::Visible)
	, WidgetName(std::move(InWidgetName))
	, WidgetOrder(InWidgetOrder)
	, Anchor(EAnchor::None)
	, DefaultAnchor(EAnchor::Center)
	, ClippingMethod(EClipping::Cut)
	, WidgetManagementInterface(InWidgetManagementInterface)
	, bWasRenderedThisFrame(false)
{
#if _DEBUG
	ENSURE_VALID(WidgetManagementInterface != nullptr);
#endif
}

void FWidget::ReceiveTick()
{
	TickWidgets();
	
	HandleInput();

	Tick();
}

void FWidget::ReceiveRender()
{
	Render();
	
	RenderWidgets();
}

void FWidget::Init()
{
	WidgetManagementInterface->RegisterWidget(this);

	SetAnchor(DefaultAnchor);

	RefreshWidget();
}

void FWidget::DeInit()
{
#if _DEBUG
	if (ENSURE_VALID(WidgetManagementInterface != nullptr))
	{
		WidgetManagementInterface->UnRegisterWidget(this);
	}
#else
	WidgetManagementInterface->UnRegisterWidget(this);
#endif
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

void FWidget::ReCalculate()
{
	RefreshWidget(false);

	for (FWidget* Widget : ManagedWidgets)
	{
		Widget->OnWindowChanged();
	}
}

FVector2D<int> FWidget::GetWidgetManagerOffset() const
{
	return GetWidgetLocationAbsolute();
}

FVector2D<int> FWidget::GetWidgetManagerSize() const
{
	return GetWidgetSize();
}

bool FWidget::HasWidgetManagerOwner() const
{
	return true;
}

IWidgetManagementInterface* FWidget::GetWidgetManagerOwner() const
{
	return GetParent();
}

FWindow* FWidget::GetOwnerWindow() const
{
	return WidgetManagementInterface->GetOwnerWindow();
}

void FWidget::OnWindowChanged()
{
	ReCalculate();
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
	SetWidgetLocationAbsoluteInternal(InWidgetLocation);

	SetAnchor(EAnchor::None);
}

FVector2D<int> FWidget::GetWidgetLocationRelative() const
{
	return WidgetLocation - GetWidgetManagerOffset();
}

void FWidget::SetWidgetLocationRelative(const FVector2D<int> InWidgetLocation)
{
	SetWidgetLocationRelativeInternal(InWidgetLocation);

	SetAnchor(EAnchor::None);
}

void FWidget::SetWidgetLocationAbsoluteInternal(const FVector2D<int> InWidgetLocation)
{
	WidgetLocation = InWidgetLocation;
}

void FWidget::SetWidgetLocationRelativeInternal(const FVector2D<int> InWidgetLocation)
{
	WidgetLocation = WidgetManagementInterface->GetWidgetManagerOffset() + InWidgetLocation;
}

FVector2D<int> FWidget::GetWidgetSize() const
{
	return WidgetSize;
}

void FWidget::SetWidgetSize(const FVector2D<int> InWidgetSize, const bool bRefreshAnchor)
{
	SetWidgetSizeInternal(InWidgetSize);

	if (bRefreshAnchor)
	{
		RefreshAnchor();
	}
}

void FWidget::SetWidgetSizeInternal(const FVector2D<int> InWidgetSize, const bool bRefreshAnchor)
{
	WidgetSize = InWidgetSize;
}

void FWidget::RefreshWidget(const bool bRefreshChilds)
{
	RefreshWidgetSize();
	RefreshAnchor();

	if (bRefreshChilds)
	{
		for (auto i = 0; i < ManagedWidgets.Size(); i++)
		{
			ManagedWidgets[i]->RefreshWidget();
		}
	}
}

void FWidget::RefreshWidgetSize()
{
	switch (ClippingMethod)
	{
	case EClipping::None:
		break;
		
	case EClipping::Resize:
		{
			const FVector2D<int> ParentSize = GetParent()->GetWidgetManagerSize();

			if (ParentSize.X < WidgetSize.X)
			{
				WidgetSize.X = ParentSize.X;
			}

			if (ParentSize.Y < WidgetSize.Y)
			{
				WidgetSize.Y = ParentSize.Y;
			}
		}
		break;
	case EClipping::Cut:
		{
			const FVector2D<int> ParentSize = GetParent()->GetWidgetManagerSize();

			if (ParentSize.X < WidgetSize.X)
			{
				WidgetSize.X = ParentSize.X;
			}

			if (ParentSize.Y < WidgetSize.Y)
			{
				WidgetSize.Y = ParentSize.Y;
			}
		}
		break;
	}
}

void FWidget::RefreshAnchor()
{
	switch (Anchor)
	{
	case EAnchor::None:
		{
			// This option means user do not want to use Anchor system.
			break;
		}
		
	case EAnchor::Center:
		{
			const FVector2D<int> ParentSize = GetParent()->GetWidgetManagerSize();
			const FVector2D<int> ThisWidgetSize = GetWidgetSize();
			
			FVector2D<int> RelativeCenter;

			RelativeCenter.X = (ParentSize.X - ThisWidgetSize.X) / 2;
			RelativeCenter.Y = (ParentSize.Y - ThisWidgetSize.Y) / 2;
			
			SetWidgetLocationAbsoluteInternal(RelativeCenter);
			break;
		}
		
	case EAnchor::LeftTop:
		{
			SetWidgetLocationAbsoluteInternal(0);
			break;
		}
		
	case EAnchor::LeftBottom:
		{
			const FVector2D<int> ParentSize = GetParent()->GetWidgetManagerSize();
			const FVector2D<int> ThisWidgetSize = GetWidgetSize();
		
			FVector2D<int> RelativeCenter;
			
			RelativeCenter.X = 0;
			RelativeCenter.Y = ParentSize.Y - ThisWidgetSize.Y;
			
			SetWidgetLocationAbsoluteInternal(RelativeCenter);
			break;
		}
		
	case EAnchor::RightTop:
		{
			const FVector2D<int> ParentSize = GetParent()->GetWidgetManagerSize();
			const FVector2D<int> ThisWidgetSize = GetWidgetSize();
		
			FVector2D<int> RelativeCenter;
			
			RelativeCenter.X = ParentSize.X - ThisWidgetSize.X;
			RelativeCenter.Y = 0;
			
			SetWidgetLocationAbsoluteInternal(RelativeCenter);
			break;
		}
		
	case EAnchor::RightBottom:
		{
			const FVector2D<int> ParentSize = GetParent()->GetWidgetManagerSize();
			const FVector2D<int> ThisWidgetSize = GetWidgetSize();
		
			FVector2D<int> RelativeCenter;
			
			RelativeCenter.X = ParentSize.X - ThisWidgetSize.X;
			RelativeCenter.Y = ParentSize.Y - ThisWidgetSize.Y;
			
			SetWidgetLocationAbsoluteInternal(RelativeCenter);
			break;
		}
		
	case EAnchor::TopCenter:
		{
			const FVector2D<int> ParentSize = GetParent()->GetWidgetManagerSize();
			const FVector2D<int> ThisWidgetSize = GetWidgetSize();
		
			FVector2D<int> RelativeCenter;
			
			RelativeCenter.X = (ParentSize.X - ThisWidgetSize.X) / 2;
			RelativeCenter.Y = 0;
			
			SetWidgetLocationAbsoluteInternal(RelativeCenter);
			break;
		}
		
	case EAnchor::LeftCenter:
		{
			const FVector2D<int> ParentSize = GetParent()->GetWidgetManagerSize();
			const FVector2D<int> ThisWidgetSize = GetWidgetSize();
		
			FVector2D<int> RelativeCenter;
			
			RelativeCenter.X = 0;
			RelativeCenter.Y = (ParentSize.Y - ThisWidgetSize.Y) / 2;
			
			SetWidgetLocationAbsoluteInternal(RelativeCenter);
			break;
		}
		
	case EAnchor::BottomCenter:
		{
			const FVector2D<int> ParentSize = GetParent()->GetWidgetManagerSize();
			const FVector2D<int> ThisWidgetSize = GetWidgetSize();
		
			FVector2D<int> RelativeCenter;
			
			RelativeCenter.X = (ParentSize.X - ThisWidgetSize.X) / 2;
			RelativeCenter.Y = ParentSize.Y - ThisWidgetSize.Y;
			
			SetWidgetLocationAbsoluteInternal(RelativeCenter);
			break;
		}
		
	case EAnchor::RightCenter:
		{
			const FVector2D<int> ParentSize = GetParent()->GetWidgetManagerSize();
			const FVector2D<int> ThisWidgetSize = GetWidgetSize();
		
			FVector2D<int> RelativeCenter;
			
			RelativeCenter.X = ParentSize.X - ThisWidgetSize.X;
			RelativeCenter.Y = (ParentSize.Y - ThisWidgetSize.Y) / 2;
			
			SetWidgetLocationAbsoluteInternal(RelativeCenter);
			break;
		}
	}
}

void FWidget::SetAnchor(const EAnchor NewAnchor)
{
	if (Anchor != NewAnchor)
	{
		OnAnchorChanged(NewAnchor);
	}
}

EAnchor FWidget::GetAnchor() const
{
	return Anchor;
}

void FWidget::OnAnchorChanged(const EAnchor NewAnchor)
{
	Anchor = NewAnchor;
	
	RefreshAnchor();
}

IWidgetManagementInterface* FWidget::GetParent() const
{
	return WidgetManagementInterface;
}

IWidgetManagementInterface* FWidget::GetParentRoot() const
{
	if (WidgetManagementInterface != nullptr)
	{
		if (const FWidget* ParentWidget = dynamic_cast<FWidget*>(WidgetManagementInterface))
		{
			return ParentWidget->GetParentRoot();
		}
		
		if (WidgetManagementInterface->HasWidgetManagerOwner())
		{
			return WidgetManagementInterface->GetWidgetManagerOwner();
		}
	}

	return nullptr;
}

EClipping FWidget::GetClippingMethod() const
{
	return ClippingMethod;
}

void FWidget::SetClippingMethod(const EClipping NewClippingMethod)
{
	if (ClippingMethod != NewClippingMethod)
	{
		ClippingMethod = NewClippingMethod;
		
		OnClippingMethodChanged(NewClippingMethod);
	}
}

void FWidget::OnClippingMethodChanged(EClipping NewClipping)
{
}
