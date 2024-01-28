#include "CoreEngine.h"
#include "Renderer/Widgets/WidgetInputManager.h"

#include "Input/EventHandler.h"

FWidgetInputManager::FWidgetInputManager()
{
	FEventHandler* EventHandler = GEngine->GetEventHandler();
	if (EventHandler != nullptr)
	{
		EventHandler->OnMouseMoved.BindObject(this, &FWidgetInputManager::OnMouseMoved);
	}
}

FWidgetInputManager::~FWidgetInputManager()
{
	FEventHandler* EventHandler = GEngine->GetEventHandler();
	if (EventHandler != nullptr)
	{
		EventHandler->OnMouseMoved.RemoveObject(this, &FWidgetInputManager::OnMouseMoved);
	}
}

void FWidgetInputManager::Register(FWidget* NewWidget)
{
	if (NewWidget->GetWidgetOrder() == WIDGET_DEFINES_DEFAULT_ORDER)
	{
		WidgetsArray.Push(NewWidget);
	}
	else
	{
		ChangeOrder(NewWidget);
	}

	if (IWidgetManagementInterface* Parent = NewWidget->GetParent())
	{
		Parent->OnWidgetOrderChanged.BindObject(this, &FWidgetInputManager::ChangeOrder);
	}
}

void FWidgetInputManager::UnRegister(FWidget* NewWidget)
{
	if (IWidgetManagementInterface* Parent = NewWidget->GetParent())
	{
		Parent->OnWidgetOrderChanged.RemoveObject(this, &FWidgetInputManager::ChangeOrder);
	}

	WidgetsArray.Remove(NewWidget);
}

void FWidgetInputManager::ChangeOrder(FWidget* Widget)
{
	if (Widget->GetWidgetOrder() != WIDGET_DEFINES_DEFAULT_ORDER)
	{
		IWidgetManagementInterface* Parent = Widget->GetParent();

		const auto ManagedWidgetsNum = WidgetsArray.Size();
		const int WidgetOrder = Widget->GetWidgetOrder();

		for (auto i = 0; i < ManagedWidgetsNum; i++)
		{
			FWidget* CurrentWidget = WidgetsArray[i];

			if (CurrentWidget->GetWidgetOrder() < WidgetOrder)
			{
				WidgetsArray.Remove(Widget);
				WidgetsArray.InsertAt(i, CurrentWidget);
			}
		}
	}
}

void FWidgetInputManager::OnMouseMoved(const FVector2D<int> Location)
{
	bool bInputConsumed = false;

	const FFunctorLambda<void, FFunctorBase<bool, FVector2D<int>>*, FVector2D<int>> Lambda(
	[&] (FFunctorBase<bool, FVector2D<int>>* Function, const FVector2D<int> InLocation)
	{
		if (!bInputConsumed)
		{
			if (bool FunctionResult = Function->operator()(InLocation))
			{
				bInputConsumed = true;
			}
		}
	});

	OnMouseMovedDelegate.ExecuteByLambda(Lambda, Location);
}
