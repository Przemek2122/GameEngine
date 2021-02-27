// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"
#include "../Widget.h"

class FInteractionBaseWidget : public FWidget
{
public:
	FInteractionBaseWidget(IWidgetManagementInterface* InWidgetManagementInterface, const std::string& InWidgetName);
	virtual ~FInteractionBaseWidget() override;
	
	/** Begin FWidget interface */
	virtual void HandleInput() override;
	virtual void Tick() override;
	virtual void Render() override;
	/** End FWidget interface */

	static _NODISCARD FVector2D<int> GetMouseLocation();
	static _NODISCARD bool GetClickInput();

	/** Called once when clicked in widget area. */
	virtual void NativeClick();
	/** Called every frame when hovered. */
	virtual void NativeHover();

protected:
	bool bWasClicked;
	
};
