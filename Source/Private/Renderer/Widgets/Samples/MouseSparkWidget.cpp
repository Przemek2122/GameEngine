// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Renderer/Widgets/Samples/MouseSparkWidget.h"
#include "Input/EventHandler.h"

FMouseSparkWidget::FMouseSparkWidget(FWidgetManager* InWidgetManager, const std::string InWidgetName)
	: FWidget(InWidgetManager, InWidgetName)
	, NumOfFrames(125)
{
}

FMouseSparkWidget::~FMouseSparkWidget()
{
}

void FMouseSparkWidget::Tick()
{
	Super::Tick();

	if (GetWidgetManager()->GetOwnerWindow()->IsWindowFocused())
	{
		auto* EventHandler = Engine->GetEventHandler();

		const FVector2D<int> MouseLocation = EventHandler->GetMouseLocationCurrent();

		ScreenLocations.PushBack(MouseLocation);

		if (ScreenLocations.Size() > static_cast<unsigned int>(NumOfFrames))
		{
			ScreenLocations.DequeFront();
		}
	}
}

void FMouseSparkWidget::Render()
{
	Super::Render();

	for (size_t i = 0; i < ScreenLocations.Size(); i++)
	{
		RenderSparkAt(ScreenLocations[i]);
	}
}

void FMouseSparkWidget::RenderSparkAt(const FVector2D<int>& ScreenPosition)
{
	if (FRenderer* Renderer = GetRenderer())
	{
		Renderer->DrawPointAt(FColorPoint(ScreenPosition, FColorRGBA(200, 30, 70)));
	}
}
