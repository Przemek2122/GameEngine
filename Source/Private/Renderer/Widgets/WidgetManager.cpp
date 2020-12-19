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

void FWidgetManager::Init()
{
}

void FWidgetManager::Update()
{
	const auto Size = ManagedWidgets.Size();
	
	for (int i = 0; i < Size; i++)
	{
		ManagedWidgets[i]->Update();
	}
}

void FWidgetManager::Render()
{
	const auto Size = ManagedWidgets.Size();
	
	for (int i = 0; i < Size; i++)
	{
		ManagedWidgets[i]->Render();
	}
}

void FWidgetManager::RegisterWidget(FWidget* Widget)
{
	ManagedWidgets.Push(Widget);
}

void FWidgetManager::UnRegisterWidget(FWidget* Widget)
{
	ManagedWidgets.Remove(Widget);
}
