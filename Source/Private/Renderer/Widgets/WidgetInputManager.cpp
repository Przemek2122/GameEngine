#include "CoreEngine.h"
#include "Renderer/Widgets/WidgetInputManager.h"

#include "Input/EventHandler.h"
#include "Renderer/Widgets/WidgetInputInterface.h"

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
	const FEventHandler* EventHandler = GEngine->GetEventHandler();
	if (EventHandler != nullptr)
	{
		//auto Ptr = FAutoDeletePointer<FWidgetInputWrapper<void, FVector2D<int>>>();

		//EventHandler->MouseMoveDelegate->Delegate.BindObject(Ptr.Get(), &FWidgetInputWrapper<void, FVector2D<int>>::Execute);

		OnMouseMove = std::move(CreateMouseWidgetInputWrapper<FVector2D<int>>(
			EventHandler->MouseMoveDelegate.Get()
		));

		OnMouseLeftButtonPress = CreateMouseWidgetInputConsumableWrapper<FVector2D<int>>(
			EventHandler->MouseLeftButtonPressDelegate.Get(),
			WIDGET_CONSUME_INPUT_ALLOW
		);

		OnMouseLeftButtonRelease = CreateMouseWidgetInputConsumableWrapper<FVector2D<int>>(
			EventHandler->MouseLeftButtonReleaseDelegate.Get(),
			WIDGET_CONSUME_INPUT_ALLOW
		);
		/*
		*/
	}
}

FWidgetInputManager::~FWidgetInputManager()
{
	const FEventHandler* EventHandler = GEngine->GetEventHandler();
	if (EventHandler != nullptr)
	{
		RemoveMouseWidgetInputWrapper<FVector2D<int>>(EventHandler->MouseMoveDelegate.Get(), OnMouseMove.Get());
		RemoveMouseWidgetInputConsumableWrapper<FVector2D<int>>(EventHandler->MouseLeftButtonPressDelegate.Get(), OnMouseLeftButtonPress.Get());
		RemoveMouseWidgetInputConsumableWrapper<FVector2D<int>>(EventHandler->MouseLeftButtonReleaseDelegate.Get(), OnMouseLeftButtonRelease.Get());
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

void FWidgetInputManager::UnRegister(FWidget* NewWidget)
{
	if (IWidgetManagementInterface* Parent = NewWidget->GetParent())
	{
		Parent->OnWidgetOrderChanged.UnBindObject(this, &FWidgetInputManager::ChangeOrder);
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
