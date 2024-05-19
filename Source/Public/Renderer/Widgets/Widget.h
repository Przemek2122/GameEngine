// See https://github.com/Przemek2122/GameEngine

#pragma once

#include "CoreMinimal.h"

#include "WidgetsPositionInterface.h"
#include "WidgetEnums.h"

class FWidgetInputManager;
class FInteractionBaseWidget;

/** 
 * Widgets can be created only from within FWidgetManager which is inside window or inside other widgets.
 * It's mostly to ensure widget render in proper window.
 *
 * LifeCycle:
 * Widget is Created using IWidgetManagementInterface it inherits from. @See CreateWidget inside of this interface.
 * Widget is destroying in same interface using DestroyWidget or DestroyWidget on widget you would like to destroy.
 * @Note It's worth mentioning that after destroying it's kept for one frame to ensure proper destruction of all children.
 */
class FWidget : public FObject, public IWidgetPositionInterface
{
	friend IWidgetManagementInterface;

protected:
	/** If creating outside manager make sure to send proper IWidgetManagementInterface. Otherwise exception will be thrown in debug. */
	FWidget(IWidgetManagementInterface* InWidgetManagementInterface, std::string InWidgetName, const int InWidgetOrder = WIDGET_DEFINES_DEFAULT_ORDER);
	~FWidget() override;

	/** Advanced, use Tick() if possible instead. */
	virtual void ReceiveTick();

	/** Advanced, use Render() if possible instead. */
	virtual void ReceiveRender();

	/** Called right after construction\n Usage: Set default size, bind delegates etc...*/
	virtual void Init() override;

	/** Called before DestroyWidget */
	virtual void PreDeInit();

	/** Called right before destruction, @NOTE PreDeInit is called earlier. */
	virtual void DeInit();

	/** Called each frame.\n Should be used for code logic. */
	virtual void Tick();

	/** Called each frame.\n Should be used To draw data only. */
	virtual void Render();

	/** Called when there is a need for recalculating cached data eg:\n Window size changed. */
	virtual void ReCalculate();

public:
	void DestroyWidget();
	void FinalizeDestroyWidget();

	/** Currently a hack - Do not use at all. */
	void DestroyWidgetImmediate();

	/** True if DestroyWidget() has been called already */
	bool IsPendingDelete() const { return bIsPendingDelete; }

	/** Full widget refresh. Performance heavy. */
	virtual void RefreshWidget(const bool bRefreshChildren = true);

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

	bool IsVisible() const;

	virtual void OnWidgetVisibilityChanged();

	/** Name of this widget. Can be displayed or widget can be get using this variable. */
	_NODISCARD std::string GetName() const;

	_NODISCARD int GetWidgetOrder() const;

	void SetWidgetOrder(const int InWidgetOrder);

	virtual void OnWidgetOrderChanged();

	/** @returns parent IWidgetManagementInterface pointer */
	_NODISCARD IWidgetManagementInterface* GetParent() const override;

	/** @returns first parent (top of tree) */
	_NODISCARD IWidgetManagementInterface* GetParentRoot() const;

	bool IsInteractive() const;

protected:
	/** True if WidgetManagementInterface decided to render this widget. */
	bool bWasRenderedThisFrame;

private:
	/** True if widget is initialized */
	bool bWasInitCalled;

	/** Name of this widget. Can be displayed or widget can be get using this variable. */
	std::string WidgetName;

	/** Order - Higher = render first, interact first */
	int WidgetOrder;

	/** Visibility state of widget */
	EWidgetVisibility WidgetVisibility;

	/** Owner manager */
	IWidgetManagementInterface* WidgetManagementInterface;

	bool bIsPendingDelete;
	
};
