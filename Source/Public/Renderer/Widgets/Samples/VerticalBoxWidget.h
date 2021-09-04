// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"
#include "../Widget.h"

class FVerticalBoxWidget : public FWidget
{
public:
	FVerticalBoxWidget(IWidgetManagementInterface* InWidgetManagementInterface, const std::string& InWidgetName, const int InWidgetOrder = 0);

	/** Begin FWidget interface */
	virtual void Render() override;
	/** End FWidget interface */

	/** Begin IWidgetManagementInterface interface */
	void RegisterWidget(FWidget* Widget) override;
	void UnRegisterWidget(FWidget* Widget) override;
	/** End IWidgetManagementInterface interface */
	
	void AlignWidgets();

};
