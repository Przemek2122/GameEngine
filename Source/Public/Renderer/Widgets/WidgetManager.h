// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"
#include "WidgetsManagementInterface.h"

/**
 * Interactive UI rendering.
 */
class FWidgetManager : public IWidgetManagementInterface
{
	friend FWindow;
	
protected:
	FWidgetManager(FWindow* InOwnerWindow);
	virtual ~FWidgetManager() override;

	virtual void DeInit();
	virtual void ReceiveTick();

	/** Begin IWidgetManagementInterface */
	_NODISCARD virtual FVector2D<int> GetWidgetManagerOffset() const override;
	_NODISCARD virtual FVector2D<int> GetWidgetManagerSize() const override;
	_NODISCARD virtual bool HasParent() const override;
	_NODISCARD virtual IWidgetManagementInterface* GetParent() const override;
	_NODISCARD virtual FWindow* GetOwnerWindow() const override;
	virtual void OnWindowChanged() override;
	/** End IWidgetManagementInterface */

private:
	/** Window where widgets are rendered */
	FWindow* OwnerWindow;

	/** Window size */
	FVector2D<int> WidgetManagerSize;
	
};
