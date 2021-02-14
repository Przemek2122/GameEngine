// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Renderer/Widgets/Widget.h"
#include "Renderer/Widgets/WidgetManager.h"

FWidget::FWidget(FWidgetManager* InWidgetManager, const std::string InWidgetName)
	: WidgetManager(InWidgetManager)
	, WidgetVisibility(EWidgetVisibility::Visible)
	, WidgetName(std::move(InWidgetName))
	, WidgetOrder(0)
{
#if _DEBUG
	if (WidgetManager == nullptr)
	{
		ENSURE_VALID_MESSAGE(false, "Widget with no widget manager should not exists! Please fix InWidgetManager pointer.");
	}
#endif
	
	WidgetManager->RegisterWidget(this);
}

FWidget::~FWidget()
{
#if _DEBUG
	if (WidgetManager == nullptr)
	{
		ENSURE_VALID_MESSAGE(false, "Widget with no widget manager should not exists!");
	}
#endif
	
	WidgetManager->UnRegisterWidget(this);
}

void FWidget::HandleInput()
{
}

void FWidget::Tick()
{
}

void FWidget::Render()
{
}

bool FWidget::ShouldBeRendered() const
{
	return (WidgetVisibility == EWidgetVisibility::Visible || WidgetVisibility == EWidgetVisibility::VisibleNotInteractive);
}

FWidgetManager* FWidget::GetWidgetManager() const
{
#if _DEBUG
	if (WidgetManager == nullptr)
	{
		ENSURE_VALID_MESSAGE(false, "Requested FWidgetManager but it has not been created!");
	}
#endif
	
	return WidgetManager;
}

FWindow* FWidget::GetWindow() const
{
	return WidgetManager->GetOwnerWindow();
}

FRenderer* FWidget::GetRenderer() const
{
	return GetWindow()->GetRenderer();
}

FEventHandler* FWidget::GetEventHandler()
{
	return Engine->GetEventHandler();
}

void FWidget::SetWidgetVisibility(const EWidgetVisibility InWidgetVisibility)
{
	WidgetVisibility = InWidgetVisibility;
}

EWidgetVisibility FWidget::GetWidgetVisibility() const
{
	return WidgetVisibility;
}

std::string FWidget::GetName() const
{
	return WidgetName;
}

int FWidget::GetWidgetOrder() const
{
	return WidgetOrder;
}

void FWidget::SetWidgetOrder(const int InWidgetOrder)
{
	WidgetOrder = InWidgetOrder;
	
	OnWidgetOrderChanged();
}

void FWidget::OnWidgetOrderChanged()
{
	WidgetManager->ChangeWidgetOrder(this);
}

FVector2D<int> FWidget::GetWidgetLocation() const
{
	return WidgetLocation;
}

void FWidget::SetWidgetLocation(const FVector2D<int> InWidgetLocation)
{
	WidgetLocation = InWidgetLocation;
}

FVector2D<int> FWidget::GetWidgetSize() const
{
	return WidgetSize;
}

void FWidget::SetWidgetSize(const FVector2D<int> InWidgetSize)
{
	WidgetSize = InWidgetSize;
}
