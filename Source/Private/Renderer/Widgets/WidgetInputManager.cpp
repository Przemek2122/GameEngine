#include "CoreEngine.h"
#include "Renderer/Widgets/WidgetInputManager.h"

#include "Input/EventHandler.h"

enum
{
	WIDGET_CONSUME_INPUT_ALLOW = 1,
	WIDGET_CONSUME_INPUT_DENY = 0
};

FWidgetInputManager::FWidgetInputManager()
{
	FEventHandler* EventHandler = GEngine->GetEventHandler();
	if (EventHandler != nullptr)
	{
		MouseMoveInput = FAutoDeletePointer<FWidgetInputWrapper<bool, FVector2D<int>>>(WIDGET_CONSUME_INPUT_DENY);
		EventHandler->OnMouseMoved.BindObject(MouseMoveInput.Get(), &FWidgetInputWrapper<bool, FVector2D<int>>::Exectute);
	}
}

FWidgetInputManager::~FWidgetInputManager()
{
	FEventHandler* EventHandler = GEngine->GetEventHandler();
	if (EventHandler != nullptr)
	{
		EventHandler->OnMouseMoved.RemoveObject(MouseMoveInput.Get(), &FWidgetInputWrapper<bool, FVector2D<int>>::Exectute);
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
