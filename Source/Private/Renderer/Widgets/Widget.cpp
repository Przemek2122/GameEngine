// See https://github.com/Przemek2122/GameEngine

#include "CoreEngine.h"
#include "Renderer/Widgets/Widget.h"

#include "Renderer/Widgets/WidgetInputManager.h"

FWidget::FWidget(IWidgetManagementInterface* InWidgetManagementInterface, std::string InWidgetName, const int InWidgetOrder)
	: IWidgetPositionInterface(InWidgetManagementInterface)
	, bWasRenderedThisFrame(false)
	, bWasInitCalled(false)
	, WidgetName(std::move(InWidgetName))
	, WidgetOrder(InWidgetOrder)
	, WidgetVisibility(EWidgetVisibility::Visible)
	, WidgetManagementInterface(InWidgetManagementInterface)
	, bIsPendingDelete(false)
	, WidgetInputManager(nullptr)
#if WITH_WIDGET_DEBUGGER
	, bIsWidgetBeingDebugged(false)
#endif
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
	bWasRenderedThisFrame = ShouldBeRendered();
	if (bWasRenderedThisFrame)
	{
		Render();

		RenderWidgets();
	}

#if WITH_WIDGET_DEBUGGER
	if (bIsWidgetBeingDebugged)
	{
		FRenderer* Renderer = GetRenderer();
		Renderer->DrawRectangleOutline(GetWidgetLocation(), GetWidgetSize(), FColorRGBA::ColorRed(), false);
	}
#endif
}

void FWidget::Init()
{
	WidgetManagementInterface->RegisterWidget(this);

	SetAnchor(DefaultAnchor);

	RegisterWidgetPostInit(this);

	bWasInitCalled = true;

	// Register input
	FDelegate<void, FWidgetInputManager*> SetupDelegate;
	SetupDelegate.BindObject(this, &FWidget::SetupInput);

	WidgetInputManager = GetWindow()->GetWidgetInputManager();
	WidgetInputManager->Register(this, SetupDelegate);
}

void FWidget::PreDeInit()
{
	if (WidgetInputManager != nullptr)
	{
		// Unregister input
		FDelegate<void, FWidgetInputManager*> ClearDelegate;
		ClearDelegate.BindObject(this, &FWidget::ClearInput);

		WidgetInputManager->UnRegister(this, ClearDelegate);
	}
	else
	{
		LOG_WARN("Unable to unregister input for widget.");
	}

	// Unregister widget
	if (WidgetManagementInterface != nullptr)
	{
		WidgetManagementInterface->UnRegisterWidget(this);

		WidgetManagementInterface = nullptr;
	}
}

void FWidget::DeInit()
{
}

void FWidget::Tick()
{
}

void FWidget::Render()
{
}

void FWidget::OnWidgetOrderChanged()
{
	WidgetManagementInterface->ChangeWidgetOrder(this);
}

void FWidget::OnWidgetVisibilityChanged()
{
}

void FWidget::OnChildSizeChanged()
{
	Super::OnChildSizeChanged();

	UpdateSizeToFitChildren();
}

void FWidget::OnMouseMove(FVector2D<int> InMousePosition, EInputState InputState)
{
}

bool FWidget::OnMouseLeftClick(FVector2D<int> InMousePosition, EInputState InputState)
{
	// By default, we do not capture input on widgets, you can change returned value to true to block input for other input receivers
	return false;
}

bool FWidget::OnMouseRightClick(FVector2D<int> InMousePosition, EInputState InputState)
{
	// By default, we do not capture input on widgets, you can change returned value to true to block input for other input receivers
	return false;
}

void FWidget::SetupInput(FWidgetInputManager* InWidgetInputManager)
{
	InWidgetInputManager->MouseInputCollection.OnMouseMove.Get()->BindObject(this, &FWidget::OnMouseMove);
	InWidgetInputManager->MouseInputCollection.OnMouseLeftButtonUsed.Get()->BindObject(this, &FWidget::OnMouseLeftClick);
	InWidgetInputManager->MouseInputCollection.OnMouseRightButtonUsed.Get()->BindObject(this, &FWidget::OnMouseRightClick);
}

void FWidget::ClearInput(FWidgetInputManager* InWidgetInputManager)
{
	InWidgetInputManager->MouseInputCollection.OnMouseMove.Get()->UnBindObject(this, &FWidget::OnMouseMove);
	InWidgetInputManager->MouseInputCollection.OnMouseLeftButtonUsed.Get()->UnBindObject(this, &FWidget::OnMouseLeftClick);
	InWidgetInputManager->MouseInputCollection.OnMouseRightButtonUsed.Get()->UnBindObject(this, &FWidget::OnMouseRightClick);
}

void FWidget::UpdateSizeToFitChildren()
{
	// @TODO Refactor due to widget changes
	if (bShouldChangeSizeToFitChildren)
	{
		FVector2D<int> DesiredSize;

		for (const FWidget* ChildWidget : ManagedWidgets)
		{
			if (ChildWidget->IsVisible())
			{
				const FVector2D<int> ChildSize = ChildWidget->GetWidgetSize();

				if (ChildSize.X > DesiredSize.X)
				{
					DesiredSize.X = ChildSize.X;
				}

				DesiredSize.Y += ChildSize.Y;
			}
		}

		const FVector2D<int> CurrentWidgetSize = GetWidgetSize();

		if (DesiredSize.X > CurrentWidgetSize.X && DesiredSize.Y > CurrentWidgetSize.Y)
		{
			SetWidgetSize(DesiredSize);
		}
		else if (DesiredSize.X > CurrentWidgetSize.X)
		{
			DesiredSize.Y = CurrentWidgetSize.Y;

			SetWidgetSize(DesiredSize);
		}
		else if (DesiredSize.Y > CurrentWidgetSize.Y)
		{
			DesiredSize.X = CurrentWidgetSize.X;

			SetWidgetSize(DesiredSize);
		}

		UpdateAnchor();
	}
}

void FWidget::DestroyWidget()
{
	if (!bIsPendingDelete)
	{
		RequestWidgetRebuild();

		bIsPendingDelete = true;

		PreDeInit();

		ClearChildren();

		GEngine->GetFunctionsToCallOnStartOfNextTick().BindObject(this, &FWidget::FinalizeDestroyWidget);
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

void FWidget::DestroyWidgetImmediate()
{
	if (!bIsPendingDelete)
	{
		bIsPendingDelete = true;

		ClearChildren();

		PreDeInit();

		DeInit();

		delete this;
	}
}

void FWidget::SetWidgetVisibility(const EWidgetVisibility InWidgetVisibility)
{
	if (WidgetVisibility != InWidgetVisibility)
	{
		WidgetVisibility = InWidgetVisibility;

		// TODO: Not sure if this is correct approach
		for (FWidget* ManagedWidget : ManagedWidgets)
		{
			ManagedWidget->SetWidgetVisibility(InWidgetVisibility);
		}

		RequestWidgetRebuild();
	}
}

void FWidget::SetWidgetOrder(const int InWidgetOrder)
{
	WidgetOrder = InWidgetOrder;

	OnWidgetOrderChanged();
}

void FWidget::SetShouldChangeSizeOnChildChange(const bool bInShouldChangeSizeOnChildChange)
{
	bShouldChangeSizeToFitChildren = bInShouldChangeSizeOnChildChange;
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
	// Widgets unlike FWidgetManager always have parent
	return true;
}

FWindow* FWidget::GetOwnerWindow() const
{
	return WidgetManagementInterface->GetOwnerWindow();
}

void FWidget::OnWindowChanged()
{
	RequestWidgetRebuild();

	for (FWidget* ManagedWidget : ManagedWidgets)
	{
		ManagedWidget->OnWindowChanged();
	}
}

bool FWidget::IsVisible() const
{
	return (WidgetVisibility == EWidgetVisibility::Visible || WidgetVisibility == EWidgetVisibility::VisibleNotInteractive);
}

bool FWidget::IsInteractive() const
{
	return (GetWidgetVisibility() == EWidgetVisibility::Visible || GetWidgetVisibility() == EWidgetVisibility::Hidden);
}

bool FWidget::ShouldBeRendered() const
{
	return (WidgetVisibility == EWidgetVisibility::Visible || WidgetVisibility == EWidgetVisibility::VisibleNotInteractive);
}

std::string FWidget::GetName() const
{
	return WidgetName;
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

EWidgetVisibility FWidget::GetWidgetVisibility() const
{
	return WidgetVisibility;
}

int FWidget::GetWidgetOrder() const
{
	return WidgetOrder;
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

#if WITH_WIDGET_DEBUGGER
void FWidget::SetIsWidgetBeingDebugged(const bool bNewValue)
{
	bIsWidgetBeingDebugged = bNewValue;
}
#endif
