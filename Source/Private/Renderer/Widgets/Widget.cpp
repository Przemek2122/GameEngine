// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Renderer/Widgets/Widget.h"

#include "Renderer/Widgets/WidgetManager.h"


FWidget::FWidget(FWidgetManager* InWidgetManager)
	: WidgetManager(InWidgetManager)
	, WidgetVisibility(EWidgetVisibility::Visible)
{
	InWidgetManager->RegisterWidget(this);
}

FWidget::~FWidget()
{
	WidgetManager->UnRegisterWidget(this);
}

void FWidget::Init()
{
}

void FWidget::Tick()
{
}

void FWidget::Render()
{
}

FWidgetManager const* FWidget::GetWidgetManager() const
{
#if _DEBUG
	if (WidgetManager == nullptr)
	{
		ENSURE("Requested FWidgetManager but it has not been created!");
	}
#endif
	
	return WidgetManager;
}

void FWidget::GetWidgetVisibility(const EWidgetVisibility InWidgetVisibility)
{
	WidgetVisibility = InWidgetVisibility;
}

EWidgetVisibility FWidget::GetWidgetVisibility() const
{
	return WidgetVisibility;
}
