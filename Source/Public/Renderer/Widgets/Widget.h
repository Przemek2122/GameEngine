// See https://github.com/Przemek2122/GameEngine

#pragma once

#include "CoreMinimal.h"

#include "WidgetsPositionInterface.h"
#include "WidgetsManagementInterface.h"
#include "WidgetEnums.h"

class FInteractionBaseWidget;

/** 
 * Widgets can be created only from within FWidgetManager which is inside window or inside other widgets.
 * It's mostly to ensure widget render in proper window. 
 */
class FWidget : public IWidgetPositionInterface
{
	friend IWidgetManagementInterface;
	friend FInteractionBaseWidget;

protected:
	/** If creating outside manager make sure to send proper IWidgetManagementInterface. Otherwise exception will be thrown in debug. */
	FWidget(IWidgetManagementInterface* InWidgetManagementInterface, std::string InWidgetName, const int InWidgetOrder = 0);
	virtual ~FWidget() override = default;

	/** Advanced, use Tick() if possible instead. */
	virtual void ReceiveTick();
	/** Advanced, use Render() if possible instead. */
	virtual void ReceiveRender();

	/** Called right after construction\n Usage: Set default size, bind delegates etc...*/
	virtual void Init();
	/** Called right before destruction */
	virtual void DeInit();
	/** Called on all widgets before Tick(), should be used for input actions like click etc... */
	virtual void HandleInput();
	/** Called each frame.\n Should be used for code logic. */
	virtual void Tick();
	/** Called each frame.\n Should be used To draw data only. */
	virtual void Render();
	/** Called when there is a need for recalculating cached data eg:\n Window size changed. */
	virtual void ReCalculate();
	
	/** Full widget refresh. Performance heavy. */
	virtual void RefreshWidget(const bool bRefreshChilds = true);

public:
	/** Begin IWidgetManagementInterface */
	_NODISCARD virtual FVector2D<int> GetWidgetManagerOffset() const override;
	_NODISCARD virtual FVector2D<int> GetWidgetManagerSize() const override;
	_NODISCARD virtual bool HasParent() const override;
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
	/** Name of this widget. Can be displayed or widget can be get using this variable. */
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
	/** @returns parent IWidgetManagementInterface pointer */
	_NODISCARD IWidgetManagementInterface* GetParent() const override;
	/** @returns first parent (top of tree) */
	_NODISCARD IWidgetManagementInterface* GetParentRoot() const;

private:
	/** Owner manager */
	IWidgetManagementInterface* WidgetManagementInterface;

protected:
	/** True if WidgetManagementInterface decided to render this widget. */
	bool bWasRenderedThisFrame;
	
};
