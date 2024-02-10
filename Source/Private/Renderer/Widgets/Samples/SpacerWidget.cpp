#include "CoreEngine.h"
#include "Renderer/Widgets/Samples/SpacerWidget.h"

FSpacerWidget::FSpacerWidget(IWidgetManagementInterface* InWidgetManagementInterface, const std::string& InWidgetName, int InWidgetOrder)
	: FWidget(InWidgetManagementInterface, InWidgetName, InWidgetOrder)
{
}
