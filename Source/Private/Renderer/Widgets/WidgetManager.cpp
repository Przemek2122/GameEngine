// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Renderer/Widgets/WidgetManager.h"
#include "Renderer/Widgets/Widget.h"

FWidgetManager::FWidgetManager(FWindow* InOwnerWindow)
	: OwnerWindow(InOwnerWindow)
{
}

FWidgetManager::~FWidgetManager()
{
	const auto Size = ManagedWidgets.Size();
	
	for (auto i = 0; i < Size; i++)
	{
		delete ManagedWidgets[i];
	}

	ManagedWidgets.Clear();
}

void FWidgetManager::Tick()
{
	const auto Size = ManagedWidgets.Size();
	
	for (auto i = 0; i < Size; i++)
	{
		ManagedWidgets[i]->Tick();
	}
}

void FWidgetManager::Render()
{
	const auto Size = ManagedWidgets.Size();
	
	for (auto i = 0; i < Size; i++)
	{
		ManagedWidgets[i]->Render();
	}
}

bool FWidgetManager::DestroyWidget(FWidget* Widget)
{
	const bool bIsRemoved = ManagedWidgets.Remove(Widget) && ManagedWidgetsMap.Remove(Widget->GetName());
	
	return bIsRemoved;
}

bool FWidgetManager::DestroyWidget(const std::string& InWidgetName)
{
	if (ManagedWidgetsMap.ContainsKey(InWidgetName))
	{
		if (FWidget* Widget = GetWidgetByName(InWidgetName))
		{
			return ManagedWidgets.Remove(Widget) && ManagedWidgetsMap.Remove(InWidgetName);		
		}
	}

	return false;
}

FWidget* FWidgetManager::GetWidgetByName(const std::string& InWidgetName)
{
	return ManagedWidgetsMap.FindValueByKey(InWidgetName);
}

bool FWidgetManager::HasWidget(const std::string& InWidgetName)
{
	return ManagedWidgetsMap.ContainsKey(InWidgetName);
}

bool FWidgetManager::HasWidget(FWidget* InWidget)
{
	return ManagedWidgetsMap.ContainsValue(InWidget);
}

FWindow* FWidgetManager::GetOwnerWindow() const
{
	return OwnerWindow;
}

void FWidgetManager::RegisterWidget(FWidget* Widget)
{
	ManagedWidgets.Push(Widget);
}

void FWidgetManager::UnRegisterWidget(FWidget* Widget)
{
	ManagedWidgets.Remove(Widget);
}
