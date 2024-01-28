// See https://github.com/Przemek2122/GameEngine

#include "CoreEngine.h"
#include "Renderer/Widgets/Widget.h"

FWidget::FWidget(IWidgetManagementInterface* InWidgetManagementInterface, std::string InWidgetName, const int InWidgetOrder)
	: IWidgetPositionInterface(InWidgetManagementInterface)
	, bWasRenderedThisFrame(false)
	, bWasInitCalled(false)
	, WidgetName(std::move(InWidgetName))
	, WidgetOrder(InWidgetOrder)
	, WidgetVisibility(EWidgetVisibility::Visible)
	, WidgetManagementInterface(InWidgetManagementInterface)
	, bIsPendingDelete(false)
{
#if _DEBUG
	// Critical to be valid.
	ENSURE_VALID(WidgetManagementInterface != nullptr);
#endif
}

void FWidget::ReceiveTick()
{
	TickWidgets();

	Tick();
}

void FWidget::ReceiveRender()
{
	Render();
	
	RenderWidgets();
}

void FWidget::Init()
{
	Super::Init();

	WidgetManagementInterface->RegisterWidget(this);

	SetAnchor(DefaultAnchorInterface);

	RefreshWidget();

	RegisterWidgetPostInit(this);

	bWasInitCalled = true;
}

void FWidget::DeInit()
{
#if _DEBUG
	if (ENSURE_VALID(WidgetManagementInterface != nullptr))
	{
		WidgetManagementInterface->UnRegisterWidget(this);

		WidgetManagementInterface = nullptr;
	}
#else
	WidgetManagementInterface->UnRegisterWidget(this);
#endif
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

void FWidget::OnWidgetDestroyed()
{
}

void FWidget::DestroyWidget()
{
	if (!bIsPendingDelete)
	{
		OnWidgetDestroyed();

		FFunctorLambda<void> DeleteFunctor = [&]
		{
			DeInit();

			delete this;
		};

		GEngine->AddLambdaToCallOnStartOfNextTick(DeleteFunctor);

		bIsPendingDelete = true;
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

bool FWidget::HasParent() const
{
	return true;
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
	return GEngine->GetEventHandler();
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
		
		if (WidgetManagementInterface->HasParent())
		{
			return WidgetManagementInterface->GetParent();
		}
	}

	return nullptr;
}
