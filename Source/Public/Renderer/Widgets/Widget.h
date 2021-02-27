// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"

class FInteractionBaseWidget;
class IWidgetManagementInterface;

/** Visibility and hit control enum */
enum class EWidgetVisibility : Uint8
{
	None,
	Visible,				// Visible and interactive
	VisibleNotInteractive,	// Visible but not interactive
	Hidden,					// Not visible but interactive
	Collapsed,				// Not visible and non interactive
};

/** Alignment of parent widget control */
enum class EAnchor : Uint8
{
	None,					// Should be internal use only.
	Center,					// Center of parent widget
	LeftTop,				// Left top corner
	LeftBottom,				// left bottom corner
	RightTop,				// Right top corner
	RightBottom,			// Right bottom corner
	TopCenter,				// Center of top edge
	LeftCenter,				// Center of left edge
	BottomCenter,			// Center of bottom edge
	RightCenter				// Center of right edge
};

/** 
 * Widgets can be created only from within FWidgetManager which is inside window or inside other widgets.
 * It's mostly to ensure widget render in proper window. 
 */
class FWidget : public IWidgetManagementInterface
{
	friend IWidgetManagementInterface;
	friend FInteractionBaseWidget;

protected:
	/** If creating outside manager make sure to send proper IWidgetManagementInterface. Otherwise exception will be thrown in debug. */
	FWidget(IWidgetManagementInterface* InWidgetManagementInterface, const std::string InWidgetName, const int InWidgetOrder = 0);
	virtual ~FWidget() override;

	virtual void ReceiveTick();
	virtual void ReceiveRender();
	
	/** Called on all widgets before Tick(), should be used for input actions like click etc... */
	virtual void HandleInput();
	/** Called each frame. */
	virtual void Tick();
	/** Called each frame. Should be used To draw data only. */
	virtual void Render();

	/** Begin IWidgetManagementInterface */
	virtual FVector2D<int> GetWidgetManagerOffset() const override;
	virtual FVector2D<int> GetWidgetManagerSize() const override;
	_NODISCARD virtual FWindow* GetOwnerWindow() const override;
	/** End IWidgetManagementInterface */
	
	/** Decides if Render() should be called, affects all children */
	_NODISCARD virtual bool ShouldBeRendered() const;

public:
	_NODISCARD FWindow* GetWindow() const;
	_NODISCARD FRenderer* GetRenderer() const;
	static _NODISCARD FEventHandler* GetEventHandler();

public:
	void SetWidgetVisibility(const EWidgetVisibility InWidgetVisibility);
	_NODISCARD EWidgetVisibility GetWidgetVisibility() const;

private:
	/** Visibility state of widget */
	EWidgetVisibility WidgetVisibility;

public:
	_NODISCARD std::string GetName() const;

private:
	/** Name of this widget. Can be displayed or widget can be get using this variable. */
	std::string WidgetName;

public:
	_NODISCARD int GetWidgetOrder() const;
	void SetWidgetOrder(const int InWidgetOrder);
	virtual void OnWidgetOrderChanged();

private:
	/** Order - Higher = render first, interact first */
	int WidgetOrder;

public:
	_NODISCARD virtual FVector2D<int> GetWidgetLocationAbsolute() const;
	virtual void SetWidgetLocationAbsolute(const FVector2D<int> InWidgetLocation);
	_NODISCARD virtual FVector2D<int> GetWidgetLocationRelative() const;
	virtual void SetWidgetLocationRelative(const FVector2D<int> InWidgetLocation);
	
	_NODISCARD virtual FVector2D<int> GetWidgetSize() const;
	virtual void SetWidgetSize(const FVector2D<int> InWidgetSize, const bool bUpdateAnchor = true);

private:
	/** Current widget location top left corner location */
	FVector2D<int> WidgetLocation;

	/** Size of this widget */
	FVector2D<int> WidgetSize;

public:
	void SetAnchor(EAnchor NewAnchor);
	_NODISCARD EAnchor GetAnchor() const;
	void UpdateAnchor();

	virtual void OnAnchorChanged(EAnchor NewAnchor);

private:
	/** Anchor of this widget. Used to align to parent. */
	EAnchor Anchor;
	EAnchor DefaultAnchor;

public:
	_NODISCARD IWidgetManagementInterface* GetManagementInterface() const;

private:
	/** Owner manager */
	IWidgetManagementInterface* WidgetManagementInterface;

protected:
	/** True if WidgetManagementInterface decied to render this widget. */
	bool bWasRenderedThisFrame;
	
};
