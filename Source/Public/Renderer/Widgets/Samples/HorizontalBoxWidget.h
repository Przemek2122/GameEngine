// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "../Widget.h"

enum class EHorizontalBoxAlignMethod
{
	/** One by one starting from the left of the right */
	FromTheLeft,
};

class FHorizontalBoxWidget : public FWidget
{
public:
	FHorizontalBoxWidget(IWidgetManagementInterface* InWidgetManagementInterface, const std::string& InWidgetName, const int InWidgetOrder = WIDGET_DEFINES_DEFAULT_ORDER);

	/** Begin FWidget interface */
	void Init() override;
	void Render() override;
	void ReCalculate() override;
	/** End FWidget interface */

	/** Begin IWidgetManagementInterface interface */
	void RegisterWidgetPostInit(FWidget* Widget) override;
	void UnRegisterWidget(FWidget* Widget) override;
	/** End IWidgetManagementInterface interface */

	void AlignWidgets();
	void AlignFromTheLeft();

protected:
	EHorizontalBoxAlignMethod HorizontalBoxAlignMethod;
	bool bScaleToContent;
	
};
