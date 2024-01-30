#pragma once

#include "CoreMinimal.h"

/**
 * Class responsible for receiving and pushing input for any widget which was registered
 */
template<typename TReturnType, typename... TInParams>
class FWidgetInputWrapper
{
public:
	FWidgetInputWrapper(const bool bInCanConsumeInput)
		: bCanConsumeInput(bInCanConsumeInput)
	{
	}

	virtual void Exectute(TInParams... Params)
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

		OnMouseMovedDelegate.ExecuteByLambda(Lambda, Params...);
	}

	void BindLambda(const FFunctorLambda<TReturnType, TInParams...>& Lambda)
	{
		OnMouseMovedDelegate.BindLambda(Lambda);
	}

	void UnbindLambda(const FFunctorLambda<TReturnType, TInParams...>& Lambda)
	{
		OnMouseMovedDelegate.UnbindLambda(Lambda);
	}

	void BindObject(FFunctorObject<TReturnType, TInParams...>* Object)
	{
		OnMouseMovedDelegate.BindObject(Object);
	}

	void UnbindObject(FFunctorObject<TReturnType, TInParams...>* Object)
	{
		OnMouseMovedDelegate.UnbindObject(Object);
	}

protected:
	FDelegate<TReturnType, TInParams...> OnMouseMovedDelegate;
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
	void Register(FWidget* NewWidget);
	/** If it was registered it must be later unregistered */
	void UnRegister(FWidget* NewWidget);

	/** Function triggered when widget changes order to make sure it's always handle input in correct way, first visible, first takes input */
	void ChangeOrder(FWidget* Widget);

	FAutoDeletePointer<FWidgetInputWrapper<bool, FVector2D<int>>> MouseMoveInput;

protected:
	/** Widgets which should be asked about input */
	CArray<FWidget*> WidgetsArray;

};
