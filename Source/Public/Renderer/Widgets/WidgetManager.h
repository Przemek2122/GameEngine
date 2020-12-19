// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"

class FWidget;

class FWidgetManager
{
friend FWidget;
	
protected:
	FWidgetManager();
	~FWidgetManager();

public:
	virtual void Init();

	virtual void Update();

	virtual void Render();

protected:
	void RegisterWidget(FWidget* Widget);
	void UnRegisterWidget(FWidget* Widget);

protected:
	CArray<FWidget*> ManagedWidgets;
	
};
