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

/** 
 * Widgets can be created only from within FWidgetManager which is inside window.
 * It's mostly to ensure widget render in proper window. 
 */
class FWidget
{
	friend FWidgetManager;

protected:
	/** If creating outside manager make sure to send proper InWidgetManager. Otherwise exception will be thrown in debug. */
	FWidget(FWidgetManager* InWidgetManager, const std::string& InWidgetName);
	virtual ~FWidget();
	
	virtual void Tick();
	virtual void Render();

public:
	_NODISCARD FWidgetManager* GetWidgetManager() const;
	_NODISCARD FWindow* GetWindow() const;
	_NODISCARD FRenderer* GetRenderer() const;
	
	void SetWidgetVisibility(const EWidgetVisibility InWidgetVisibility);
	_NODISCARD EWidgetVisibility GetWidgetVisibility() const;

	_NODISCARD std::string GetName() const;
	
protected:
	FWidgetManager* WidgetManager;
	EWidgetVisibility WidgetVisibility;
	std::string WidgetName;
	
};
