// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Renderer/Widgets/WidgetsManagementInterface.h"

IWidgetManagementInterface::IWidgetManagementInterface()
{
}

IWidgetManagementInterface::~IWidgetManagementInterface()
{
	const auto Size = ManagedWidgets.Size();
	
	for (auto i = 0; i < Size; i++)
	{
		delete ManagedWidgets[i];
	}

	ManagedWidgets.Clear();
}

void IWidgetManagementInterface::TickWidgets()
{
	const auto Size = ManagedWidgets.Size();
	
	for (size_t i = 0; i < Size; i++)
	{
		ManagedWidgets[i]->ReceiveTick();
	}
}

void IWidgetManagementInterface::RenderWidgets()
{
	const auto Size = ManagedWidgets.Size();
	
	for (size_t i = 0; i < Size; i++)
	{
		ManagedWidgets[i]->bWasRenderedThisFrame = ManagedWidgets[i]->ShouldBeRendered();
		
		if (ManagedWidgets[i]->bWasRenderedThisFrame)
		{
			ManagedWidgets[i]->ReceiveRender();
		}
	}
}

bool IWidgetManagementInterface::DestroyWidget(FWidget* Widget)
{
	const bool bIsRemoved = ManagedWidgets.Remove(Widget) && ManagedWidgetsMap.Remove(Widget->GetName());
	
	return bIsRemoved;
}

bool IWidgetManagementInterface::DestroyWidget(const std::string& InWidgetName)
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

FWidget* IWidgetManagementInterface::GetWidgetByName(const std::string& InWidgetName)
{
	return ManagedWidgetsMap.FindValueByKey(InWidgetName);
}

bool IWidgetManagementInterface::HasWidget(const std::string& InWidgetName)
{
	return ManagedWidgetsMap.ContainsKey(InWidgetName);
}

bool IWidgetManagementInterface::HasWidget(FWidget* InWidget)
{
	return ManagedWidgetsMap.ContainsValue(InWidget);
}

void IWidgetManagementInterface::ChangeWidgetOrder(FWidget* InWidget)
{
	const auto ManagedWidgetsNum = ManagedWidgets.Size();
	const int WidgetOrder = InWidget->GetWidgetOrder();

	for (int i = 0; i < ManagedWidgetsNum; i++)
	{
		FWidget* CurrentWidget = ManagedWidgets[i];
		
		if (CurrentWidget->GetWidgetOrder() < WidgetOrder)
		{
			ManagedWidgets.Remove(InWidget);
			ManagedWidgets.InsertAt(i, CurrentWidget);
		}
	}	
}

void IWidgetManagementInterface::RegisterWidget(FWidget* Widget)
{
#if _DEBUG
	const auto WidgetIndex = ManagedWidgets.FindIndexOf(Widget);
	ENSURE_VALID_MESSAGE(WidgetIndex == -1, "Re-Register of widget is not allowed");
#endif
	
	ManagedWidgets.Push(Widget);
	ManagedWidgetsMap.InsertOrAssign(Widget->GetName(), Widget);
}

void IWidgetManagementInterface::UnRegisterWidget(FWidget* Widget)
{
#if _DEBUG
	const auto IndexToDelete = ManagedWidgets.FindIndexOf(Widget);
	ENSURE_VALID_MESSAGE(IndexToDelete != -1, "Tried to remove not existing widget!");
#endif
	
	ManagedWidgets.Remove(Widget);
	ManagedWidgetsMap.Remove(Widget->GetName());

#if _DEBUG
	const auto NotDeletedIndex = ManagedWidgets.FindIndexOf(Widget);
	ENSURE_VALID_MESSAGE(NotDeletedIndex == -1, "Widget not removed!");
#endif
}

