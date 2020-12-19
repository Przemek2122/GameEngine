// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Renderer/Widgets/Widget.h"

#include "Renderer/Widgets/WidgetManager.h"


FWidget::FWidget(FWidgetManager* InWidgetManager)
	: WidgetManager(InWidgetManager)
	, WidgetVisibility(Visible)
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

void FWidget::Update()
{
}

void FWidget::Render()
{
}

FWidgetManager const* FWidget::GetWidgetManager() const
{
	return WidgetManager;
}

EWidgetVisibility FWidget::GetWidgetVisibility() const
{
	return WidgetVisibility;
}
