#include "CoreEngine.h"
#include "Renderer/Widgets/WidgetInputManager.h"

#include "Input/EventHandler.h"
#include "Input/WindowInputManager.h"

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

FWidgetInputManager::FWidgetInputManager(FWindow* InOwnerWindow)
	: OwnerWindow(InOwnerWindow)
{
	if (InOwnerWindow != nullptr)
	{
		SetupMouseDelegates();
		SetupKeyboardDelegates();
	}
}

FWidgetInputManager::~FWidgetInputManager()
{
	if (OwnerWindow != nullptr)
	{
		ClearMouseDelegates();
		ClearKeyboardDelegates();
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

		for (ContainerInt i = 0; i < ManagedWidgetsNum; i++)
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

void FWidgetInputManager::SetupMouseDelegates()
{
	FWindowInputManager* WindowInputManager = OwnerWindow->GetWindowInputManager();

	MouseInputCollection.OnMouseMove = CreateMouseWidgetInputWrapper<FVector2D<int>, EInputState>(
		WindowInputManager->MouseDelegates.GetMouseDelegateByName("MOUSE_MOVE")
	);

	MouseInputCollection.OnMouseLeftButtonUsed = CreateMouseWidgetInputConsumableWrapper<FVector2D<int>, EInputState>(
		WindowInputManager->MouseDelegates.GetMouseDelegateByName("MOUSE_BUTTON_LEFT"),
		WIDGET_CONSUME_INPUT_ALLOW
	);

	MouseInputCollection.OnMouseRightButtonUsed = CreateMouseWidgetInputConsumableWrapper<FVector2D<int>, EInputState>(
		WindowInputManager->MouseDelegates.GetMouseDelegateByName("MOUSE_BUTTON_RIGHT"),
		WIDGET_CONSUME_INPUT_ALLOW
	);
}

void FWidgetInputManager::SetupKeyboardDelegates()
{
	FWindowInputManager* WindowInputManager = OwnerWindow->GetWindowInputManager();

	KeyboardInputCollection.OnEscapeUsed = FAutoDeletePointer<FWidgetInputConsumableWrapper<bool, EInputState>>(WIDGET_CONSUME_INPUT_ALLOW);

	WindowInputManager->KeyBoardDelegates.ButtonEscape.Get()->Delegate.BindObject(
		KeyboardInputCollection.OnEscapeUsed.Get(), &FWidgetInputConsumableWrapper<bool, EInputState>::ExecuteByLambda
	);
}

void FWidgetInputManager::ClearMouseDelegates()
{
	FWindowInputManager* WindowInputManager = OwnerWindow->GetWindowInputManager();

	RemoveMouseWidgetInputWrapper<FVector2D<int>, EInputState>(
		WindowInputManager->MouseDelegates.GetMouseDelegateByName("MOUSE_MOVE"), MouseInputCollection.OnMouseMove.Get()
	);

	RemoveMouseWidgetInputConsumableWrapper<FVector2D<int>, EInputState>(
		WindowInputManager->MouseDelegates.GetMouseDelegateByName("MOUSE_BUTTON_LEFT"), MouseInputCollection.OnMouseLeftButtonUsed.Get()
	);

	RemoveMouseWidgetInputConsumableWrapper<FVector2D<int>, EInputState>(
		WindowInputManager->MouseDelegates.GetMouseDelegateByName("MOUSE_BUTTON_RIGHT"), MouseInputCollection.OnMouseRightButtonUsed.Get()
	);
}

void FWidgetInputManager::ClearKeyboardDelegates()
{
	FWindowInputManager* WindowInputManager = OwnerWindow->GetWindowInputManager();

	WindowInputManager->KeyBoardDelegates.ButtonEscape.Get()->Delegate.UnBindObject(
		KeyboardInputCollection.OnEscapeUsed.Get(), &FWidgetInputConsumableWrapper<bool, EInputState>::ExecuteByLambda
	);
}
