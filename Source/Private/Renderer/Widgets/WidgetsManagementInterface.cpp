// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Renderer/Widgets/WidgetsManagementInterface.h"

IWidgetManagementInterface::IWidgetManagementInterface()
	: LastWidgetNumber(0)
{
}

IWidgetManagementInterface::~IWidgetManagementInterface()
{
	ClearChildren();
}

void IWidgetManagementInterface::TickWidgets()
{
	auto Size = ManagedWidgets.Size();
	
	for (auto i = 0; i < Size; i++)
	{
		ManagedWidgets[i]->ReceiveTick();
	}
}

void IWidgetManagementInterface::RenderWidgets()
{
	const auto Size = ManagedWidgets.Size();
	
	for (auto i = 0; i < Size; i++)
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

			RegisterWidgetPostInit(InWidget);

			return true;
		}
	}

	return false;
}

bool IWidgetManagementInterface::DestroyWidget(FWidget* Widget)
{
	if (ENSURE_VALID(Widget != nullptr))
	{
		Widget->DestroyWidget();

		OnChildWidgetDestroyed(Widget);

		return (ManagedWidgets.Remove(Widget) && ManagedWidgetsMap.Remove(Widget->GetName()));
	}
	
	return false;
}

bool IWidgetManagementInterface::DestroyWidget(const std::string& InWidgetName)
{
	if (ManagedWidgetsMap.ContainsKey(InWidgetName))
	{
		FWidget* Widget = GetWidgetByName(InWidgetName);
		if (ENSURE_VALID(Widget != nullptr))
		{
			Widget->DestroyWidget();

			OnChildWidgetDestroyed(Widget);

			return (ManagedWidgets.Remove(Widget) && ManagedWidgetsMap.Remove(InWidgetName));		
		}
	}

	return false;
}

void IWidgetManagementInterface::ClearChildren()
{
	for (auto i = ManagedWidgets.Size() - 1; i >= 0; i--)
	{
		ManagedWidgets[i]->DestroyWidget();
	}
}

int IWidgetManagementInterface::GetChildrenCount() const
{
	return ManagedWidgets.Size();
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

void IWidgetManagementInterface::OnChildWidgetCreated(FWidget* NewWidget)
{
	AddChild(NewWidget);
}

void IWidgetManagementInterface::OnChildWidgetDestroyed(FWidget* NewWidget)
{
}

void IWidgetManagementInterface::ChangeWidgetOrder(FWidget* InWidget)
{
	const auto ManagedWidgetsNum = ManagedWidgets.Size();
	const int WidgetOrder = InWidget->GetWidgetOrder();

	for (auto i = 0; i < ManagedWidgetsNum; i++)
	{
		FWidget* CurrentWidget = ManagedWidgets[i];
		
		if (CurrentWidget->GetWidgetOrder() < WidgetOrder)
		{
			ManagedWidgets.Remove(InWidget);
			ManagedWidgets.InsertAt(i, CurrentWidget);

			OnWidgetOrderChanged.Execute(InWidget);
		}
	}	
}

void IWidgetManagementInterface::RegisterWidget(FWidget* Widget)
{
#if _DEBUG
	const auto WidgetIndex = ManagedWidgets.FindIndexOf(Widget);
	ENSURE_VALID(WidgetIndex == -1);
#endif
	
	ManagedWidgets.InsertByLambda(Widget, [&](FWidget* ArrayObject, FWidget* Localobject)
	{
		if (ArrayObject->GetWidgetOrder() > Localobject->GetWidgetOrder())
		{
			return true;
		}

		return false;
	});
	ManagedWidgetsMap.InsertOrAssign(Widget->GetName(), Widget);

	if (Widget->GetParent() != this)
	{
		// This means re-register to same parent and it's not supported
		ENSURE_VALID(false);
	}
}

void IWidgetManagementInterface::RegisterWidgetPostInit(FWidget* Widget)
{
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
