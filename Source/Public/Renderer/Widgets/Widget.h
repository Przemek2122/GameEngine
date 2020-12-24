// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"

enum class EWidgetVisibility : Uint8
{
	None,
	Visible,
};

class FWidgetManager;

class FWidget
{
	friend FWidgetManager;

protected:
	FWidget(FWidgetManager* InWidgetManager);
	~FWidget();

	virtual void Init();

	virtual void Tick();

	virtual void Render();

public:
	_NODISCARD FWidgetManager const* GetWidgetManager() const;
	void GetWidgetVisibility(const EWidgetVisibility InWidgetVisibility);
	_NODISCARD EWidgetVisibility GetWidgetVisibility() const;
	
protected:
	FWidgetManager* WidgetManager;
	EWidgetVisibility WidgetVisibility;
	
};
