#include "CoreEngine.h"
#include "Renderer/Widgets/WidgetInputManager.h"

#include "Input/EventHandler.h"

enum
{
	WIDGET_CONSUME_INPUT_ALLOW = 1,
	WIDGET_CONSUME_INPUT_DENY = 0
};

// Create FAutoDeletePointer with FWidgetInputWrapper with templated type
// Make sure to use FAutoDeletePointer to avoid memory leaks and to use RemoveMouseWidgetInputConsumableWrapper to remove it from delegate
template<typename ...TParams>
auto CreateMouseWidgetInputWrapper(FMouseInputDelegateWrapper* DelegateWrapper)
{
	FWidgetInputWrapper<void, TParams...>* Ptr = new FWidgetInputWrapper<void, TParams...>();

	DelegateWrapper->Delegate.BindObject(Ptr, &FWidgetInputWrapper<void, TParams...>::Execute);

	return FAutoDeletePointer<FWidgetInputWrapper<void, TParams...>>(Ptr);
}

// Create FAutoDeletePointer with FWidgetInputWrapper with templated type
// Make sure to use FAutoDeletePointer to avoid memory leaks and to use RemoveMouseWidgetInputConsumableWrapper to remove it from delegate
template<typename ...TParams>
auto CreateMouseWidgetInputConsumableWrapper(FMouseInputDelegateWrapper* DelegateWrapper, int bConsumeInput)
{
	FWidgetInputConsumableWrapper<bool, TParams...>* Ptr = new FWidgetInputConsumableWrapper<bool, TParams...>(bConsumeInput);

	DelegateWrapper->Delegate.BindObject(Ptr, &FWidgetInputConsumableWrapper<bool, TParams...>::ExecuteByLambda);

	return FAutoDeletePointer<FWidgetInputConsumableWrapper<bool, TParams...>>(Ptr);
}

// Remove FWidgetInputWrapper from FMouseInputDelegateWrapper
template<typename ...TParams>
void RemoveMouseWidgetInputWrapper(FMouseInputDelegateWrapper* DelegateWrapper, FWidgetInputWrapper<void, TParams...>* Ptr)
{
	DelegateWrapper->Delegate.UnBindObject(Ptr, &FWidgetInputWrapper<void, TParams...>::Execute);
}

// Remove FWidgetInputWrapper from FMouseInputDelegateWrapper
template<typename ...TParams>
void RemoveMouseWidgetInputConsumableWrapper(FMouseInputDelegateWrapper* DelegateWrapper, FWidgetInputConsumableWrapper<bool, TParams...>* Ptr)
{
	DelegateWrapper->Delegate.UnBindObject(Ptr, &FWidgetInputConsumableWrapper<bool, TParams...>::ExecuteByLambda);
}

FWidgetInputManager::FWidgetInputManager()
{
	FEventHandler* EventHandler = GEngine->GetEventHandler();
	if (EventHandler != nullptr)
	{
		SetupMouseDelegates(EventHandler);
		SetupKeyboardDelegates(EventHandler);
	}
}

FWidgetInputManager::~FWidgetInputManager()
{
	FEventHandler* EventHandler = GEngine->GetEventHandler();
	if (EventHandler != nullptr)
	{
		ClearMouseDelegates(EventHandler);
		ClearKeyboardDelegates(EventHandler);
	}
}

void FWidgetInputManager::Register(FWidget* NewWidget, FDelegate<void, FWidgetInputManager*>& SetupDelegate)
{
	if (NewWidget->GetWidgetOrder() == WIDGET_DEFINES_DEFAULT_ORDER)
	{
		WidgetsArray.Push(NewWidget);

		SetupDelegate.Execute(this);
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

void FWidgetInputManager::UnRegister(FWidget* NewWidget, FDelegate<void, FWidgetInputManager*>& ClearDelegate)
{
	if (IWidgetManagementInterface* Parent = NewWidget->GetParent())
	{
		Parent->OnWidgetOrderChanged.UnBindObject(this, &FWidgetInputManager::ChangeOrder);
	}

	ClearDelegate.Execute(this);

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

void FWidgetInputManager::SetupMouseDelegates(FEventHandler* EventHandler)
{
	MouseInputCollection.OnMouseMove = CreateMouseWidgetInputWrapper<FVector2D<int>, EInputState>(
		EventHandler->MouseDelegates.GetMouseDelegateByName("MOUSE_MOVE")
	);

	MouseInputCollection.OnMouseLeftButtonUsed = CreateMouseWidgetInputConsumableWrapper<FVector2D<int>, EInputState>(
		EventHandler->MouseDelegates.GetMouseDelegateByName("MOUSE_BUTTON_LEFT"),
		WIDGET_CONSUME_INPUT_ALLOW
	);
}

void FWidgetInputManager::SetupKeyboardDelegates(FEventHandler* EventHandler)
{
	KeyboardInputCollection.OnEscapeUsed = FAutoDeletePointer<FWidgetInputConsumableWrapper<bool, EInputState>>(WIDGET_CONSUME_INPUT_ALLOW);

	EventHandler->KeyBoardDelegates.ButtonEscape.Get()->Delegate.BindObject(
		KeyboardInputCollection.OnEscapeUsed.Get(), &FWidgetInputConsumableWrapper<bool, EInputState>::ExecuteByLambda
	);
}

void FWidgetInputManager::ClearMouseDelegates(FEventHandler* EventHandler)
{
	RemoveMouseWidgetInputWrapper<FVector2D<int>, EInputState>(
		EventHandler->MouseDelegates.GetMouseDelegateByName("MOUSE_MOVE"), MouseInputCollection.OnMouseMove.Get()
	);

	RemoveMouseWidgetInputConsumableWrapper<FVector2D<int>, EInputState>(
		EventHandler->MouseDelegates.GetMouseDelegateByName("MOUSE_BUTTON_LEFT"), MouseInputCollection.OnMouseLeftButtonUsed.Get()
	);
}

void FWidgetInputManager::ClearKeyboardDelegates(FEventHandler* EventHandler)
{
	EventHandler->KeyBoardDelegates.ButtonEscape.Get()->Delegate.UnBindObject(
		KeyboardInputCollection.OnEscapeUsed.Get(), &FWidgetInputConsumableWrapper<bool, EInputState>::ExecuteByLambda
	);
}
