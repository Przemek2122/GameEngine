#pragma once

#include "CoreMinimal.h"

/**
 * Class responsible for receiving and pushing input for any widget which was registered
 */
template<typename TDelegateType>
class FWidgetInputWrapper
{
public:
	virtual void Exectute();



protected:
	TDelegateType OnMouseMovedDelegate;
	
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

	void OnMouseMoved(const FVector2D<int> Location);

	FDelegate<bool, FVector2D<int>> OnMouseMovedDelegate;

	FWidgetInputWrapper<FDelegate<bool, FVector2D<int>>> MouseMoveInput;

protected:
	/** Widgets which should be asked about input */
	CArray<FWidget*> WidgetsArray;

};
