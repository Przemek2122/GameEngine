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
	FWidget(FWidgetManager* InWidgetManager, const std::string InWidgetName);
	virtual ~FWidget();

	/** Called on all widgets before Tick() */
	virtual void HandleInput();
	/** Called each frame. */
	virtual void Tick();
	/** Called each frame. Should be used To draw data only. */
	virtual void Render();
	
	/** Decides if Render() should be called? */
	_NODISCARD virtual bool ShouldBeRendered() const;

public:
	_NODISCARD FWidgetManager* GetWidgetManager() const;
	_NODISCARD FWindow* GetWindow() const;
	_NODISCARD FRenderer* GetRenderer() const;
	static _NODISCARD FEventHandler* GetEventHandler();
	
	void SetWidgetVisibility(const EWidgetVisibility InWidgetVisibility);
	_NODISCARD EWidgetVisibility GetWidgetVisibility() const;

	_NODISCARD std::string GetName() const;

	_NODISCARD int GetWidgetOrder() const;
	void SetWidgetOrder(const int InWidgetOrder);
	virtual void OnWidgetOrderChanged();

	_NODISCARD FVector2D<int> GetWidgetLocation() const;
	void SetWidgetLocation(const FVector2D<int> InWidgetLocation);
	
	_NODISCARD FVector2D<int> GetWidgetSize() const;
	_NODISCARD void SetWidgetSize(const FVector2D<int> InWidgetSize);

protected:
	/** Owner manager */
	FWidgetManager* WidgetManager;
	
	/** Visibility state of widget */
	EWidgetVisibility WidgetVisibility;
	
	/** Name of this widget. Can be displayed or widget can be get using this variable. */
	std::string WidgetName;

	/** Order - Higher = render first, interact first */
	int WidgetOrder;

	/** Current widget location top left corner location */
	FVector2D<int> WidgetLocation;

	/**  */
	FVector2D<int> WidgetSize;
	
};
