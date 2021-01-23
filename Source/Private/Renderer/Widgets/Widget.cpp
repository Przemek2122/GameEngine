// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Renderer/Widgets/Widget.h"
#include "Renderer/Widgets/WidgetManager.h"

FWidget::FWidget(FWidgetManager* InWidgetManager, const std::string& InWidgetName)
	: WidgetManager(InWidgetManager)
	, WidgetVisibility(EWidgetVisibility::Visible)
	, WidgetName(InWidgetName)
{
#if _DEBUG
	if (WidgetManager == nullptr)
	{
		static std::string WidgetManagerInNotValidNotify = "Widget with no widget manager should not exists! Please fix InWidgetManager pointer.";
		LOG_ERROR(WidgetManagerInNotValidNotify);
		ENSURE(WidgetManagerInNotValidNotify.c_str());
	}
#endif
	
	WidgetManager->RegisterWidget(this);
}

FWidget::~FWidget()
{
#if _DEBUG
	if (WidgetManager == nullptr)
	{
		static std::string WidgetManagerOutNotValidNotify = "Widget with no widget manager should not exists!.";
		ENSURE(WidgetManagerOutNotValidNotify.c_str());
	}
#endif
	
	WidgetManager->UnRegisterWidget(this);
}

void FWidget::Tick()
{
}

void FWidget::Render()
{
}

FWidgetManager* FWidget::GetWidgetManager() const
{
#if _DEBUG
	if (WidgetManager == nullptr)
	{
		static std::string WidgetManagerGetNotValidNotify = "Requested FWidgetManager but it has not been created!";
		ENSURE(WidgetManagerGetNotValidNotify.c_str());
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
