// Created by Przemysław Wiewióra 2020

#include "CoreEngine.h"
#include "Renderer/Widgets/Samples/VerticalBoxWidget.h"

FVerticalBoxWidget::FVerticalBoxWidget(IWidgetManagementInterface* InWidgetManagementInterface, const std::string& InWidgetName, const int InWidgetOrder)
	: FWidget(InWidgetManagementInterface, InWidgetName, InWidgetOrder)
	, VerticalBoxAlignMethod(EVerticalBoxAlignMethod::Default)
	, bScaleToContent(true)
	, CurrentlyCalculatedNumberOfWidgets(0)
{
}

void FVerticalBoxWidget::Init()
{
	SetWidgetSize({ 200, 300 });

	Super::Init();
}

void FVerticalBoxWidget::Render()
{
	Super::Render();

#if _DEBUG
	GetRenderer()->DrawRectangle(GetWidgetLocation(EWidgetOrientation::Absolute), GetWidgetSize(), FColorRGBA::ColorOrange());
#endif
}

void FVerticalBoxWidget::ReCalculate()
{
	Super::ReCalculate();

	AlignWidgets(true);
}

void FVerticalBoxWidget::RegisterWidgetPostInit(FWidget* Widget)
{
	Super::RegisterWidgetPostInit(Widget);

	AlignWidgets();
}

void FVerticalBoxWidget::UnRegisterWidget(FWidget* Widget)
{
	Super::UnRegisterWidget(Widget);

	AlignWidgets();
}

void FVerticalBoxWidget::OnChildSizeChanged()
{
	Super::OnChildSizeChanged();

	AlignWidgets(true);
}

void FVerticalBoxWidget::SetScaleToContent(const bool bNewScaleToContent)
{
	bScaleToContent = bNewScaleToContent;
}

void FVerticalBoxWidget::AlignWidgets(const bool bForce)
{
	const int CurrentNumberOfManagedWidgets = ManagedWidgets.Size();

	if (bForce || CurrentNumberOfManagedWidgets > 0 && CurrentlyCalculatedNumberOfWidgets != CurrentNumberOfManagedWidgets)
	{
		CurrentlyCalculatedNumberOfWidgets = CurrentNumberOfManagedWidgets;

		switch (VerticalBoxAlignMethod)
		{
			case EVerticalBoxAlignMethod::Default:
			{
				AlignDefault();

				break;
			}
			case EVerticalBoxAlignMethod::Even:
			{
				AlignEven();

				break;
			}
		}
	}
}

void FVerticalBoxWidget::AlignDefault()
{
	const FVector2D<int> VerticalBoxLocation = GetWidgetLocation(EWidgetOrientation::Relative);
	const FVector2D<int> VerticalBoxSize = GetWidgetSize();

	const FVector2D<int> VerticalBoxMaxBounds = VerticalBoxLocation + VerticalBoxSize;

	if (bScaleToContent)
	{
		FVector2D<int> VerticalBoxSizeCalculated = {0, 0};

		// Calculate size for parent widget
		for (ContainerInt i = 0; i < ManagedWidgets.Size(); i++)
		{
			const FWidget* ChildWidget = ManagedWidgets[i];

			// We must ensure it's only done when it should be visible
			if (ChildWidget->IsVisible())
			{
				const FVector2D<int> ChildWidgetSize = ChildWidget->GetWidgetSize();

				// Find child with the biggest width
				if (VerticalBoxSizeCalculated.X < ChildWidgetSize.X)
				{
					VerticalBoxSizeCalculated.X = ChildWidgetSize.X;
				}

				// Always add height
				VerticalBoxSizeCalculated.Y += ChildWidgetSize.Y;
			}
		}

		SetWidgetSize(VerticalBoxSizeCalculated);
	}

	FVector2D<int> AggregatedChildSizeLast = { 0, 0 };
	
	for (ContainerInt i = 0; i < ManagedWidgets.Size(); i++)
	{
		FWidget* ChildWidget = ManagedWidgets[i];

		// We must ensure it's only done when it should be visible
		if (ChildWidget->IsVisible())
		{
			FVector2D<int> NewChildLocation = VerticalBoxLocation;
			NewChildLocation.Y += AggregatedChildSizeLast.Y;

			FVector2D<int> ChildWidgetSize = ChildWidget->GetWidgetSize();

			const FVector2D<int> ChildBounds = NewChildLocation + ChildWidgetSize;

			// Make sure it fits inside box
			if (ChildBounds.X > VerticalBoxMaxBounds.X)
			{
				ChildWidgetSize.X = VerticalBoxMaxBounds.X;
			}
			if (ChildBounds.Y > VerticalBoxMaxBounds.Y)
			{
				ChildWidgetSize.Y = VerticalBoxMaxBounds.Y;
			}

			ChildWidget->SetWidgetLocation(NewChildLocation, EWidgetOrientation::Relative, true);

			AggregatedChildSizeLast.Y += ChildWidgetSize.Y;

			ChildWidget->RefreshWidget();
		}
	}
}

void FVerticalBoxWidget::AlignEven()
{
	LOG_ERROR("This method is empty. @See FVerticalBoxWidget::AlignEven");
}

void FVerticalBoxWidget::SetVerticalBoxAlignMethod(const EVerticalBoxAlignMethod InVerticalBoxAlignMethod, const bool bUpdateAfterSet)
{
	VerticalBoxAlignMethod = InVerticalBoxAlignMethod;

	if (bUpdateAfterSet)
	{
		AlignWidgets();
	}
}

EVerticalBoxAlignMethod FVerticalBoxWidget::GetVerticalBoxAlignMethod() const
{
	return VerticalBoxAlignMethod;
}
