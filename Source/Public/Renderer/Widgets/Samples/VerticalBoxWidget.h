// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"
#include "../Widget.h"

enum class EVerticalBoxAlignMethod
{
	/** One by one starting from the top of the widget */
	Default,
	/** Try to evenly divide space if possible */
	Even
};

class FVerticalBoxWidget : public FWidget
{
public:
	FVerticalBoxWidget(IWidgetManagementInterface* InWidgetManagementInterface, const std::string& InWidgetName, const int InWidgetOrder = 0);

	/** Begin FWidget interface */
	virtual void Init() override;
	virtual void Render() override;
	void ReCalculate() override;
	/** End FWidget interface */

	/** Begin IWidgetManagementInterface interface */
	void RegisterWidget(FWidget* Widget) override;
	void UnRegisterWidget(FWidget* Widget) override;
	/** End IWidgetManagementInterface interface */
	
	void AlignWidgets();

	void AlignDefault();
	void AlignEven();

	void SetVerticalBoxAlignMethod(const EVerticalBoxAlignMethod InVerticalBoxAlignMethod);
	_NODISCARD EVerticalBoxAlignMethod GetVerticalBoxAlignMethod() const;
		 
protected:
	EVerticalBoxAlignMethod VerticalBoxAlignMethod;
	
};
