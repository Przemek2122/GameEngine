// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"

/**
 * Class responsible for managing widgets. \n
 * It will be on WidgetManager class as well as on each widget as we can add widget to each of those.
 */
class IWidgetManagementInterface
{
	friend FWidget;
	
public:
	IWidgetManagementInterface();
	virtual ~IWidgetManagementInterface();

	/** @returns size, this is used to move widgets by default to relative location. */
	_NODISCARD virtual FVector2D<int> GetWidgetManagerOffset() const = 0;

	/** @returns Size of this interface. */
	_NODISCARD virtual FVector2D<int> GetWidgetManagerSize() const = 0;

	/** Get owner or nullptr if there is none */
	_NODISCARD virtual IWidgetManagementInterface* GetParent() const = 0;

	/** True if has owner */
	_NODISCARD virtual bool HasParent() const = 0;

	/**
	 * Ticking widgets works different than render. \n
	 * First child widgets are ticked than parent.
	 */
	virtual void TickWidgets();
	
	/**
	 * Rendering of widgets. \n
	 * First parent is rendered than all its child and it's children ...
	 */
	virtual void RenderWidgets();

	/**
	 * Add child by moving from other interface. \n
	 * We do not have RemoveChild because this AddChild handles removing previous parent.
	 */
	virtual bool AddChild(FWidget* InWidget);
	
	/** Create new widget from template, auto-managed. */
	template<class TWidgetTemplate>
	INLINE_DEBUGABLE TWidgetTemplate* CreateWidget(const char* InWidgetName, const int InWidgetOrder = 0)
	{
		return CreateWidget<TWidgetTemplate>(std::string(InWidgetName), InWidgetOrder);
	}

	/** Create new widget from template, auto-managed. */
	template<class TWidgetTemplate>
	INLINE_DEBUGABLE TWidgetTemplate* CreateWidget(std::string InWidgetName, const int InWidgetOrder = 0)
	{
#ifdef _DEBUG
		if (!ENSURE_VALID(!ManagedWidgetsMap.ContainsKey(InWidgetName)))
		{
			LOG_ERROR("Widget with this name already exists! Duplicate: " << InWidgetName);
		}
#endif
		
		TWidgetTemplate* CreatedWidget = new TWidgetTemplate(this, InWidgetName, InWidgetOrder);

		CreatedWidget->Init();

		OnWidgetCreated(CreatedWidget);

		return CreatedWidget;
	}

	/** Best to call Destroy widget. @returns true on success. */
	INLINE_DEBUGABLE bool DestroyWidget(FWidget* Widget);
	/** Slower overload which destroys by name. @returns true on success. */
	INLINE_DEBUGABLE bool DestroyWidget(const std::string& InWidgetName);

	/** @returns widget by name SLOW */
	_NODISCARD FWidget* GetWidgetByName(const std::string& InWidgetName);
	/** @returns widget by name SLOW - This implementation does auto deduction of type. */
	template<typename FWidgetAuto>
	_NODISCARD FWidgetAuto GetWidgetByName(const std::string& InWidgetName)
	{
		return dynamic_cast<FWidgetAuto>(GetWidgetByName(InWidgetName));
	}
	
	/** @returns true if widget with this name exists SLOW */
	bool HasWidget(const std::string& InWidgetName);
	/** @returns true if widget exists SLOW */
	bool HasWidget(FWidget* InWidget);
	
	/** @returns Window which created this manager */
	_NODISCARD virtual FWindow* GetOwnerWindow() const = 0;

	/** Called when window */
	virtual void OnWindowChanged() = 0;

	_NODISCARD const CArray<FWidget*>& GetManagedWidgets() const { return ManagedWidgets; }

	virtual void OnWidgetCreated(FWidget* NewWidget);
	virtual void OnWidgetDestroyed(FWidget* NewWidget);

protected:
	/** Called by wiget when order is changed. */
	void ChangeWidgetOrder(FWidget* InWidget);

protected:
	/** Has all widgets. First renders last, last first.... */
	CArray<FWidget*> ManagedWidgets;
	
	/** Maps string to widget. */
	CMap<std::string, FWidget*> ManagedWidgetsMap;

public:
	virtual void RegisterWidget(FWidget* Widget);
	virtual void UnRegisterWidget(FWidget* Widget);
	
};
