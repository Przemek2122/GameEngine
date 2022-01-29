// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"

class FInteractionBaseWidget;
class IWidgetManagementInterface;

/** Visibility and hit control enum */
enum class EWidgetVisibility : Uint8
{
	None,					// Should never happen
	Visible,				// Visible and interactive
	VisibleNotInteractive,	// Visible but not interactive
	Hidden,					// Not visible but interactive
	Collapsed,				// Not visible and non interactive
};

/** Alignment of parent widget control */
enum class EAnchor : Uint8
{
	None,					// Anchor system not used at all
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

/** What should happen if widget is too big? */
enum class EClipping : Uint8
{
	None,					// Do not clip
	Resize,					// Use SDL to resize if available
	Cut,					// Just cut if too big
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
	FWidget(IWidgetManagementInterface* InWidgetManagementInterface, std::string InWidgetName, const int InWidgetOrder = 0);
	virtual ~FWidget() override = default;

	virtual void ReceiveTick();
	virtual void ReceiveRender();

	/**
	 * Called right after construction
	 * Usage: Set default size, bind delegates etc...
	 */
	virtual void Init();
	/** Called right before destruction */
	virtual void DeInit();
	/** Called on all widgets before Tick(), should be used for input actions like click etc... */
	virtual void HandleInput();
	/** Called each frame. */
	virtual void Tick();
	/** Called each frame. Should be used To draw data only. */
	virtual void Render();
	/** Called when there is a need for recalculating cached data eg: Window size changed. */
	virtual void ReCalculate();

public:
	/** Begin IWidgetManagementInterface */
	_NODISCARD virtual FVector2D<int> GetWidgetManagerOffset() const override;
	_NODISCARD virtual FVector2D<int> GetWidgetManagerSize() const override;
	_NODISCARD virtual bool HasWidgetManagerOwner() const override;
	_NODISCARD virtual IWidgetManagementInterface* GetWidgetManagerOwner() const override;
	_NODISCARD virtual FWindow* GetOwnerWindow() const override;
	virtual void OnWindowChanged() override;
	/** End IWidgetManagementInterface */
	
	/** Decides if Render() should be called, affects all children */
	_NODISCARD virtual bool ShouldBeRendered() const;
	
	_NODISCARD FWindow* GetWindow() const;
	_NODISCARD FRenderer* GetRenderer() const;
	static _NODISCARD FEventHandler* GetEventHandler();
	
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

protected:
	SDL_FORCE_INLINE void SetWidgetLocationAbsoluteInternal(const FVector2D<int> InWidgetLocation);
	SDL_FORCE_INLINE void SetWidgetLocationRelativeInternal(const FVector2D<int> InWidgetLocation);
	
public:
	_NODISCARD virtual FVector2D<int> GetWidgetSize() const;
	virtual void SetWidgetSize(const FVector2D<int> InWidgetSize, const bool bRefreshAnchor = true);
	
protected:
	SDL_FORCE_INLINE void SetWidgetSizeInternal(const FVector2D<int> InWidgetSize, const bool bRefreshAnchor = true);
	
public:
	/** Called when parent widget is changed or when widget itself is changed.  */
	virtual void RefreshWidget(const bool bRefreshChilds = true);
	virtual void RefreshWidgetSize();

private:
	/** Current widget location top left corner location */
	FVector2D<int> WidgetLocation;

	/** Size of this widget */
	FVector2D<int> WidgetSize;

public:
	void RefreshAnchor();
	void SetAnchor(const EAnchor NewAnchor);
	_NODISCARD EAnchor GetAnchor() const;

	virtual void OnAnchorChanged(const EAnchor NewAnchor);

private:
	/** Anchor of this widget. Used to align to parent. */
	EAnchor Anchor;
	EAnchor DefaultAnchor;

public:
	/** @returns parent IWidgetManagementInterface pointer */
	_NODISCARD IWidgetManagementInterface* GetParent() const;
	/** @returns first parent (top of tree) */
	_NODISCARD IWidgetManagementInterface* GetParentRoot() const;

private:
	EClipping ClippingMethod;

public:
	_NODISCARD EClipping GetClippingMethod() const;
	void SetClippingMethod(const EClipping NewClippingMethod);
	virtual void OnClippingMethodChanged(EClipping NewClipping);

private:
	/** Owner manager */
	IWidgetManagementInterface* WidgetManagementInterface;

protected:
	/** True if WidgetManagementInterface decided to render this widget. */
	bool bWasRenderedThisFrame;
	
};
