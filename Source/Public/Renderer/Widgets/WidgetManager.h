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

	/** Begin IWidgetManagementInterface */
	virtual FVector2D<int> GetWidgetManagerOffset() const override;
	virtual FVector2D<int> GetWidgetManagerSize() const override;
	_NODISCARD virtual FWindow* GetOwnerWindow() const override;
	/** End IWidgetManagementInterface */

private:
	/** Window where widgets are rendered */
	FWindow* OwnerWindow;

	/** Window size */
	FVector2D<int> WidgetManagerSize;
	
};
