// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"
#include "InteractionBaseWidget.h"

class FButtonWidget : public FInteractionBaseWidget
{
public:
	FButtonWidget(FWidgetManager* InWidgetManager, const std::string& InWidgetName);
	virtual ~FButtonWidget() override;

	virtual void Tick() override;
	virtual void Render() override;

	virtual void NativeClick() override;

protected:
	FDelegate<> OnClicked;
	
	FColorRGBA ButtonColor;
	
};
