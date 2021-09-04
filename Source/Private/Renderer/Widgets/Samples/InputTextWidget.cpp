// Created by Przemys�aw Wiewi�ra 2020

#include "CoreEngine.h"
#include "Renderer/Widgets/Samples/InputTextWidget.h"

FInputTextWidget::FInputTextWidget(IWidgetManagementInterface* InWidgetManagementInterface, const std::string& InWidgetName)
	: FWidget(InWidgetManagementInterface, InWidgetName)
{
}
