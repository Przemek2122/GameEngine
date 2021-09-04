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

bool IWidgetManagementInterface::AddChild(FWidget* InWidget)
{
	if (InWidget != nullptr)
	{
		IWidgetManagementInterface* ParentInterface = InWidget->GetParent();

		if (ParentInterface != nullptr)
		{
			ParentInterface->UnRegisterWidget(InWidget);

			RegisterWidget(InWidget);

			return true;
		}
	}

	return false;
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
	ENSURE_VALID(WidgetIndex == -1);
#endif
	
	ManagedWidgets.Push(Widget);
	ManagedWidgetsMap.InsertOrAssign(Widget->GetName(), Widget);

	if (Widget->GetParent() != this)
	{
		Widget->WidgetManagementInterface = this;
	}
}

void IWidgetManagementInterface::UnRegisterWidget(FWidget* Widget)
{
#if _DEBUG
	const auto IndexToDelete = ManagedWidgets.FindIndexOf(Widget);
	ENSURE_VALID(IndexToDelete != -1);
#endif
	
	ManagedWidgets.Remove(Widget);
	ManagedWidgetsMap.Remove(Widget->GetName());

#if _DEBUG
	const auto NotDeletedIndex = ManagedWidgets.FindIndexOf(Widget);
	ENSURE_VALID(NotDeletedIndex == -1);
#endif
}
