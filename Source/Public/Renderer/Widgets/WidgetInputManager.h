#pragma once

#include "CoreMinimal.h"

enum class EInputState;

/**
 * Class responsible for receiving and pushing input for any widget which was registered
 */
template<typename TReturnType, typename... TInParams>
class FWidgetInputWrapper
{
	friend FWidgetInputManager;

public:
	FWidgetInputWrapper() = default;
	virtual ~FWidgetInputWrapper() = default;

	/** Bind lambda to delegate - Try to avoid if possible */
	void BindLambda(const FFunctorLambda<TReturnType, TInParams...>& Lambda)
	{
		Delegate.BindLambda(Lambda);
	}

	/** Unbind lambda to delegate - Try to avoid if possible lambdas */
	void UnbindLambda(const FFunctorLambda<TReturnType, TInParams...>& Lambda)
	{
		Delegate.UnbindLambda(Lambda);
	}

	/** Bind object to delegate - Best solution */
	template<typename TClass>
	void BindObject(TClass* Object, TReturnType(TClass::* InFunctionPointer)(TInParams...))
	{
		Delegate.BindObject(Object, InFunctionPointer);
	}

	/** Unbind object to delegate - Best solution */
	template<typename TClass>
	void UnBindObject(TClass* Object, TReturnType(TClass::* InFunctionPointer)(TInParams...))
	{
		Delegate.UnBindObject(Object, InFunctionPointer);
	}

	virtual bool Execute(TInParams... Params)
	{
		Delegate.Execute(Params...);

		return false;
	}

protected:
	FDelegateSafe<TReturnType, TInParams...> Delegate;

};

/**
 * Class responsible for receiving and pushing input for any widget which was registered
 * Difference between this and FWidgetInputWrapper is that this one can consume input
 */
template<typename TReturnType, typename... TInParams>
class FWidgetInputConsumableWrapper : public FWidgetInputWrapper<TReturnType, TInParams...>
{
public:
	FWidgetInputConsumableWrapper(const bool bInCanConsumeInput)
		: bCanConsumeInput(bInCanConsumeInput)
	{
	}

	/** Function which should be called when input is received */
	bool ExecuteByLambda(TInParams... Params)
	{
		bool bInputConsumed = false;

		const FFunctorLambda<void, FFunctorBase<TReturnType, TInParams...>*, TInParams...> Lambda(
			[&](FFunctorBase<TReturnType, TInParams...>* Function, TInParams... InParams)
			{
				if (!bInputConsumed)
				{
					if (bool FunctionResult = Function->operator()(InParams...))
					{
						if (bCanConsumeInput)
						{
							bInputConsumed = true;
						}
					}
				}
			});

		Super::Delegate.ExecuteByLambda(Lambda, Params...);

		return bInputConsumed;
	}

protected:
	bool bCanConsumeInput;

};

class FMouseInputCollection
{
public:
	/** Function triggered when mouse is moved */
	FAutoDeletePointer<FWidgetInputWrapper<void, FVector2D<int>, EInputState>> OnMouseMove;

	/**
	 * Function triggered when left mouse button is pressed or released @see EInputState,
	 * function should return true when pressed (blocks input for other widgets) inside and false if not.
	 */
	FAutoDeletePointer<FWidgetInputConsumableWrapper<bool, FVector2D<int>, EInputState>> OnMouseLeftButtonUsed;

	/**
	 * Function triggered when right mouse button is pressed or released @see EInputState,
	 * function should return true when pressed (blocks input for other widgets) inside and false if not.
	 */
	FAutoDeletePointer<FWidgetInputConsumableWrapper<bool, FVector2D<int>, EInputState>> OnMouseRightButtonUsed;
};

class FKeyboardInputCollection
{
public:
	/** Function triggered when key is pressed or released @see EInputState */
	FAutoDeletePointer<FWidgetInputConsumableWrapper<bool, EInputState>> OnEscapeUsed;

};

/**
 * Class responsible for giving input to the FWidget class
 */
class FWidgetInputManager
{
public:
	FWidgetInputManager(FWindow* InOwnerWindow);
	~FWidgetInputManager();

	/** Should be called when widget wants to receive input */
	void Register(FWidget* NewWidget, FDelegate<void, FWidgetInputManager*>& SetupDelegate);
	/** If it was registered it must be later unregistered */
	void UnRegister(FWidget* NewWidget, FDelegate<void, FWidgetInputManager*>& ClearDelegate);

	/** Function triggered when widget changes order to make sure it's always handle input in correct way, first visible, first takes input */
	void ChangeOrder(FWidget* Widget);

	FMouseInputCollection MouseInputCollection;
	FKeyboardInputCollection KeyboardInputCollection;

protected:
	void SetupMouseDelegates();
	void SetupKeyboardDelegates();

	void ClearMouseDelegates();
	void ClearKeyboardDelegates();

protected:
	/** Widgets which should be asked about input */
	CArray<FWidget*> WidgetsArray;

	FWindow* OwnerWindow;

};
