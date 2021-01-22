// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"

class FMouseSparkWidget : public FWidget
{
public:
	FMouseSparkWidget(FWidgetManager* InWidgetManager, std::string InWidgetName);
	virtual ~FMouseSparkWidget() override;

	/** Begin FWidget interface */
	virtual void Tick() override;
	virtual void Render() override;
	/** End FWidget interface */

	virtual void RenderSparkAt(const FVector2D<int>& ScreenPosition);

protected:
	CDeque<FVector2D<int>> ScreenLocations;	
	int NumOfFrames;
	
};
