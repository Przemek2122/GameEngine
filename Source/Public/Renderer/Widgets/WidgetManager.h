// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"

class FWidget;

class FWidgetManager
{
friend FWidget;
friend FWindow;
	
protected:
	FWidgetManager();
	~FWidgetManager();

	virtual void Init();

	virtual void Tick();

	virtual void Render();

public:
	/**
	 * Create new widget from template.
	 * Auto managed.
	 */
	template<class TWidgetTemplate>
	INLINE_DEBUGABLE TWidgetTemplate& CreateWidget()
	{
		TWidgetTemplate& CreatedWidget = new TWidgetTemplate(this);
		
		ManagedWidgets.Push(CreatedWidget);

		return CreatedWidget;
	}

	/** Destroy widget. @returns true on success. */
	INLINE_DEBUGABLE bool DestroyWidget(FWidget* Widget);

protected:
	CArray<FWidget*> ManagedWidgets;

public:
	void RegisterWidget(FWidget* Widget);
	void UnRegisterWidget(FWidget* Widget);

	
};

