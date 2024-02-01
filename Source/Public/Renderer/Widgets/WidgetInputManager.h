#pragma once

#include "CoreMinimal.h"

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
	void UnbindObject(TClass* Object, TReturnType(TClass::* InFunctionPointer)(TInParams...))
	{
		Delegate.UnbindObject(Object, InFunctionPointer);
	}

	virtual void Execute(TInParams... Params)
	{
		Delegate.Execute(Params...);
	}

protected:
	FDelegate<TReturnType, TInParams...> Delegate;

};
template<typename TReturnType, typename... TInParams>
class FWidgetInputConsumableWrapper : public FWidgetInputWrapper<TReturnType, TInParams...>
{
public:
	FWidgetInputConsumableWrapper(const bool bInCanConsumeInput)
		: bCanConsumeInput(bInCanConsumeInput)
	{
	}

	/** Function which should be called when input is received */
	void ExecuteByLambda(TInParams... Params)
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
	}

protected:
	bool bCanConsumeInput;

};

/**
 * Class responsible for giving input to the FWidget class
 */
class FWidgetInputManager
{
public:
	FWidgetInputManager();
	~FWidgetInputManager();

	/** Should be called when widget wants to receive input */
	void Register(FWidget* NewWidget, FDelegate<void, FWidgetInputManager*>& SetupDelegate);
	/** If it was registered it must be later unregistered */
	void UnRegister(FWidget* NewWidget);

	/** Function triggered when widget changes order to make sure it's always handle input in correct way, first visible, first takes input */
	void ChangeOrder(FWidget* Widget);

	/** Function triggered when mouse is moved */
	FAutoDeletePointer<FWidgetInputWrapper<void, FVector2D<int>>> OnMouseMove;
	FAutoDeletePointer<FWidgetInputConsumableWrapper<bool, FVector2D<int>>> OnMouseLeftButtonPress;
	FAutoDeletePointer<FWidgetInputConsumableWrapper<bool, FVector2D<int>>> OnMouseLeftButtonRelease;

protected:
	/** Widgets which should be asked about input */
	CArray<FWidget*> WidgetsArray;

};