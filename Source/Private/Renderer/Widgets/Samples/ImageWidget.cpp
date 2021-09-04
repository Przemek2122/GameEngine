// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Renderer/Widgets/Samples/ImageWidget.h"

FImageWidget::FImageWidget(IWidgetManagementInterface* InWidgetManagementInterface, const std::string& InWidgetName)
	: FWidget(InWidgetManagementInterface, InWidgetName)
{
}
