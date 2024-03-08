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

#if ENGINE_MEMORY_ALLOCATION_DEBUG_WIDGETS
	LOG_INFO("Widget created: '" << WidgetName << "', Widget order: " << InWidgetOrder);
#endif
}

FWidget::~FWidget()
{
#if ENGINE_MEMORY_ALLOCATION_DEBUG_WIDGETS
	LOG_INFO("Widget destroyed: '" << WidgetName);
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
	if (WidgetManagementInterface != nullptr)
	{
		WidgetManagementInterface->UnRegisterWidget(this);

		WidgetManagementInterface = nullptr;
	}
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

void FWidget::PreDeInit()
{
}

void FWidget::DestroyWidget()
{
	if (!bIsPendingDelete)
	{
		PreDeInit();

		SetWidgetVisibility(EWidgetVisibility::Collapsed);

		ClearChildren();

		GEngine->GetFunctionsToCallOnStartOfNextTick().BindObject(this, &FWidget::FinalizeDestroyWidget);

		bIsPendingDelete = true;
	}
}

void FWidget::FinalizeDestroyWidget()
{
	if (bIsPendingDelete)
	{
		DeInit();

		delete this;
	}
	else
	{
		LOG_ERROR("FinalizeDestroyWidget called but bIsPendingDelete is " << bIsPendingDelete << ". Make sure to call DestroyWidget instead.");
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

	for (FWidget* ManagedWidget : ManagedWidgets)
	{
		ManagedWidget->SetWidgetVisibility(InWidgetVisibility);
	}
}

EWidgetVisibility FWidget::GetWidgetVisibility() const
{
	return WidgetVisibility;
}

bool FWidget::IsVisible() const
{
	return (WidgetVisibility == EWidgetVisibility::Visible || WidgetVisibility == EWidgetVisibility::VisibleNotInteractive);
}

void FWidget::OnWidgetVisibilityChanged()
{
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
