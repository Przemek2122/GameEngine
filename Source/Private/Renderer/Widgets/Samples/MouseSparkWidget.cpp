// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Renderer/Widgets/Samples/MouseSparkWidget.h"
#include "Input/EventHandler.h"

FSpark::FSpark()
	: Location(0)
	, Speed(0)
	, Angle(0)
{
}

FSpark::FSpark(const FVector2D<int>& InLocation, const float InSpeed, const int InRotationDegree)
	: Location(InLocation)
	, Speed(InSpeed)
	, Angle(InRotationDegree)
{
}

FMouseSparkWidget::FMouseSparkWidget(FWidgetManager* InWidgetManager, const std::string& InWidgetName)
	: FWidget(InWidgetManager, InWidgetName)
	, MinMaxSpeedRange(0.1f, 0.4f)
	, MinMaxAngleRange(0, 359)
	, MaxNumOfPoints(256)
	, PointPerTick(8)
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
		FEventHandler* EventHandler = Engine->GetEventHandler();

		const FVector2D<int> MouseLocation = EventHandler->GetMouseLocationCurrent();

		for (int i = 0; i < PointPerTick; i++)
		{
			Sparks.PushBack(FSpark(
				MouseLocation, 
				FUtil::GetRandomValueFloating<float>(MinMaxSpeedRange.X, MinMaxSpeedRange.Y), 
				FUtil::GetRandomValue<int>(MinMaxAngleRange.X, MinMaxAngleRange.Y)
			));
		}

		while (Sparks.Size() > static_cast<unsigned int>(MaxNumOfPoints))
		{
			Sparks.DequeFront();
		}

		Points.Clear();
		Points.SetNum(Sparks.Size());
		
		for (size_t i = 0; i < Sparks.Size(); i++)
		{
			FSpark& Spark = Sparks[i];
			
			const FVector2D<float> LocationChange = FUtil::GetPointAngle<float>(Spark.Speed, static_cast<float>(Spark.Angle));
			
			Sparks[i].Location += LocationChange;

			Points[i] = Sparks[i].Location;
		}
	}
}

void FMouseSparkWidget::Render()
{
	Super::Render();
	
	if (FRenderer* Renderer = GetRenderer())
	{
		Renderer->DrawPointsAt(Points, FColorRGBA(0, 153, 154));
	}
}
