// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"

enum class EWidgetVisibility : Uint8
{
	None,
	Visible,				// Visible and interactive
	VisibleNotInteractive,	// Visible but not interactive
	Hidden,					// Not visible but interactive
	Collapsed,				// Not visible and non interactive
};

class FWidgetManager;

/** 
 * Widgets can be created only from within FWidgetManager which is inside window.
 * It's mostly to ensure widget render in proper window. 
 */
class FWidget
{
	friend FWidgetManager;

protected:
	FWidget(FWidgetManager* InWidgetManager);
	~FWidget();

	virtual void Init();

	virtual void Tick();

	virtual void Render();

public:
	_NODISCARD FWidgetManager const* GetWidgetManager() const;
	void SetWidgetVisibility(const EWidgetVisibility InWidgetVisibility);
	_NODISCARD EWidgetVisibility GetWidgetVisibility() const;
	
protected:
	FWidgetManager* WidgetManager;
	EWidgetVisibility WidgetVisibility;
	
};
