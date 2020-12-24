// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Renderer/Widgets/WidgetManager.h"
#include "Renderer/Widgets/Widget.h"


FWidgetManager::FWidgetManager()
{
}

FWidgetManager::~FWidgetManager()
{
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
	return ManagedWidgets.Remove(Widget);
}

void FWidgetManager::RegisterWidget(FWidget* Widget)
{
	ManagedWidgets.Push(Widget);
}

void FWidgetManager::UnRegisterWidget(FWidget* Widget)
{
	ManagedWidgets.Remove(Widget);
}
