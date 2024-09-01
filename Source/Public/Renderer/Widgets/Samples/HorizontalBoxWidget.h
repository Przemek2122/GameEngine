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
	void ReCalculate() override;
	/** End FWidget interface */

	/** Begin IWidgetManagementInterface interface */
	void OnAnyChildChanged() override;
	void OnChildSizeChanged() override;
	/** End IWidgetManagementInterface interface */

	void AlignWidgets(const bool bForce = false);

	void AlignFromTheLeft();

	void SetScaleToContent(const bool bInScaleToContent);

	bool ShouldScaleToContent() const { return bScaleToContent; }

protected:
	EHorizontalBoxAlignMethod HorizontalBoxAlignMethod;

	bool bScaleToContent;

	int CurrentlyCalculatedNumberOfWidgets;
	
};
