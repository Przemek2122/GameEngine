// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"
#include "Widget.h"

/**
 * Interactive UI rendering.
 */
class FWidgetManager
{
friend FWidget;
friend FWindow;
	
protected:
	FWidgetManager(FWindow* InOwnerWindow);
	virtual ~FWidgetManager();
	
	virtual void Tick();
	virtual void Render();

public:
	/**
	 * Create new widget from template.
	 * Auto managed.
	 */
	template<class TWidgetTemplate>
	INLINE_DEBUGABLE TWidgetTemplate* CreateWidget(std::string InWidgetName)
	{
		TWidgetTemplate* CreatedWidget = new TWidgetTemplate(this, InWidgetName);
		
		ManagedWidgets.Push(CreatedWidget);
		ManagedWidgetsMap.Map.emplace(InWidgetName, CreatedWidget);

		return CreatedWidget;
	}

	/** Best to call Destroy widget. @returns true on success. */
	INLINE_DEBUGABLE bool DestroyWidget(FWidget* Widget);
	/** Slower overload which destroys by name. @returns true on success. */
	INLINE_DEBUGABLE bool DestroyWidget(const std::string& InWidgetName);

	/** @returns widget by name SLOW */
	_NODISCARD FWidget* GetWidgetByName(const std::string& InWidgetName);
	
	/** @returns true if widget with this name exists SLOW */
	bool HasWidget(const std::string& InWidgetName);
	/** @returns true if widget exists SLOW */
	bool HasWidget(FWidget* InWidget);
	
	/** @returns Window which created this manager */
	_NODISCARD FWindow* GetOwnerWindow() const;

protected:
	CArray<FWidget*> ManagedWidgets;
	CMap<std::string, FWidget*> ManagedWidgetsMap;
	FWindow* OwnerWindow;

public:
	void RegisterWidget(FWidget* Widget);
	void UnRegisterWidget(FWidget* Widget);
	
};
