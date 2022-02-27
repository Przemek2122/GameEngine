// See https://github.com/Przemek2122/GameEngine

#include "CoreEngine.h"
#include "Renderer/Widgets/Widget.h"

#include <Windows.h>

FWidget::FWidget(IWidgetManagementInterface* InWidgetManagementInterface, std::string InWidgetName, const int InWidgetOrder)
	: IWidgetPositionInterface(InWidgetManagementInterface)
	, WidgetVisibility(EWidgetVisibility::Visible)
	, WidgetName(std::move(InWidgetName))
	, WidgetOrder(InWidgetOrder)
	, WidgetManagementInterface(InWidgetManagementInterface)
	, bWasRenderedThisFrame(false)
{
#if _DEBUG
	// Critical to be valid.
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

	SetAnchor(DefaultAnchorInterface);

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

void FWidget::RefreshWidget(const bool bRefreshChilds)
{
	RefreshWidgetSize();
	RefreshWidgetLocation();
	RefreshAnchor();

	if (bRefreshChilds)
	{
		for (auto i = 0; i < ManagedWidgets.Size(); i++)
		{
			ManagedWidgets[i]->RefreshWidget();
		}
	}
}

FVector2D<int> FWidget::GetWidgetManagerOffset() const
{
	return GetWidgetLocation(EWidgetOrientation::Absolute);
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
