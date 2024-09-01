// Created by Przemys�aw Wiewi�ra 2024

#pragma once

#include "CoreMinimal.h"

/**
 * UI Debugger
 */
class FWidgetDebugger
{
public:
	FWidgetDebugger(FWindow* InWindow);
	virtual ~FWidgetDebugger();

	void StartDebugger();

protected:
	void RefreshDisplayedWidgets();
	void CreateDebuggersForWidgets(FVerticalBoxWidget* InVerticalBox, const CArray<FWidget*>& InWidgets, int32 Depth);

protected:
	/** Debugged window */
	FWindow* Window;

	/** Window created for debugging primary Window */
	FWindow* DebuggerWindow;
	
};
