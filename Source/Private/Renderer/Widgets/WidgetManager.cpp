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
	
}

FVector2D<int> FWidgetManager::GetWidgetManagerOffset() const
{
	return 0;
}

FVector2D<int> FWidgetManager::GetWidgetManagerSize() const
{
	return OwnerWindow->GetWindowSize();
}

bool FWidgetManager::HasParent() const
{
	return false;
}

IWidgetManagementInterface* FWidgetManager::GetParent() const
{
	return nullptr;
}

FWindow* FWidgetManager::GetOwnerWindow() const
{
	return OwnerWindow;
}

void FWidgetManager::OnWindowChanged()
{
	for (FWidget* Widget : ManagedWidgets)
	{
		Widget->OnWindowChanged();
	}
}
