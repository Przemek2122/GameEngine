// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"

enum EWidgetVisibility : Uint8
{
	None,
	Visible,
};

class FWidgetManager;

class FWidget
{
public:
	FWidget(FWidgetManager* InWidgetManager);
	~FWidget();

	virtual void Init();

	virtual void Update();

	virtual void Render();

public:
	FWidgetManager const* GetWidgetManager() const;
	EWidgetVisibility GetWidgetVisibility() const;
	
protected:
	FWidgetManager* WidgetManager;
	EWidgetVisibility WidgetVisibility;
	
};
