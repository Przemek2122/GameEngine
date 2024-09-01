// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Renderer/Widgets/Samples/HorizontalBoxWidget.h"

#include "Misc/Math.h"

FHorizontalBoxWidget::FHorizontalBoxWidget(IWidgetManagementInterface* InWidgetManagementInterface, const std::string& InWidgetName, const int InWidgetOrder)
	: FWidget(InWidgetManagementInterface, InWidgetName, InWidgetOrder)
	, HorizontalBoxAlignMethod(EHorizontalBoxAlignMethod::FromTheLeft)
	, bScaleToContent(false)
	, CurrentlyCalculatedNumberOfWidgets(0)
{
	// This is handled by VerticalBox so we do not need to do it
	SetShouldChangeSizeOnChildChange(false);

#if WIDGET_DEBUG_COLORS
	SetWidgetDebugColor(FColorRGBA::ColorOrange());
#endif
}

void FHorizontalBoxWidget::ReCalculate()
{
	Super::ReCalculate();

	AlignWidgets(true);
}

void FHorizontalBoxWidget::RegisterWidgetPostInit(FWidget* Widget)
{
	Super::RegisterWidgetPostInit(Widget);

	AlignWidgets();
}

void FHorizontalBoxWidget::UnRegisterWidget(FWidget* Widget)
{
	Super::UnRegisterWidget(Widget);

	AlignWidgets();
}

void FHorizontalBoxWidget::OnChildSizeChanged()
{
	Super::OnChildSizeChanged();

	AlignWidgets(true);
}

void FHorizontalBoxWidget::AlignWidgets(const bool bForce)
{
	const int CurrentNumberOfManagedWidgets = ManagedWidgets.Size();

	if (bForce || (CurrentNumberOfManagedWidgets > 0 && CurrentlyCalculatedNumberOfWidgets != CurrentNumberOfManagedWidgets))
	{
		CurrentlyCalculatedNumberOfWidgets = CurrentNumberOfManagedWidgets;

		switch (HorizontalBoxAlignMethod)
		{
			case EHorizontalBoxAlignMethod::FromTheLeft:
			{
				AlignFromTheLeft();

				break;
			}
		}
	}
}

void FHorizontalBoxWidget::AlignFromTheLeft()
{
	const FVector2D<int> HorizontalBoxLocation = GetWidgetLocation(EWidgetOrientation::Relative);
	const FVector2D<int> HorizontalBoxSize = GetWidgetSize();

	const FVector2D<int> HorizontalBoxMaxBounds = HorizontalBoxLocation + HorizontalBoxSize;

	if (bScaleToContent)
	{
		FVector2D<int> HorizontalBoxSizeCalculated = { 0, 0 };

		// Calculate size for parent widget
		for (ContainerInt i = 0; i < ManagedWidgets.Size(); i++)
		{
			const FWidget* ChildWidget = ManagedWidgets[i];

			// We must ensure it's only done when it should be visible
			if (ChildWidget->IsVisible())
			{
				const FVector2D<int> ChildWidgetSize = ChildWidget->GetWidgetSize();

				// Find child with the biggest height
				if (HorizontalBoxSizeCalculated.Y < ChildWidgetSize.Y)
				{
					HorizontalBoxSizeCalculated.Y = ChildWidgetSize.Y;
				}

				// Always add width
				HorizontalBoxSizeCalculated.X += ChildWidgetSize.X;
			}
		}

		SetWidgetSize(HorizontalBoxSizeCalculated);
	}

	FVector2D<int> AggregatedChildSizeLast = { 0, 0 };

	for (ContainerInt i = 0; i < ManagedWidgets.Size(); i++)
	{
		FWidget* ChildWidget = ManagedWidgets[i];

		// We must ensure it's only done when it should be visible
		if (ChildWidget->IsVisible())
		{
			FVector2D<int> NewChildLocation = HorizontalBoxLocation;
			NewChildLocation.X += AggregatedChildSizeLast.X;

			FVector2D<int> ChildWidgetSize = ChildWidget->GetWidgetSize();

			const FVector2D<int> ChildBounds = NewChildLocation + ChildWidgetSize;

			// Make sure it fits horizontally inside the box
			if (ChildBounds.X > HorizontalBoxMaxBounds.X)
			{
				ChildWidgetSize.X = HorizontalBoxMaxBounds.X;
			}
			// Make sure it fits vertically inside the box
			if (ChildBounds.Y > HorizontalBoxMaxBounds.Y)
			{
				ChildWidgetSize.Y = HorizontalBoxMaxBounds.Y;
			}

			ChildWidget->SetWidgetLocation(NewChildLocation, EWidgetOrientation::Relative, true);

			AggregatedChildSizeLast.X += ChildWidgetSize.X;

			ChildWidget->RefreshWidget();
		}
	}
}

void FHorizontalBoxWidget::SetScaleToContent(const bool bInScaleToContent)
{
	bScaleToContent = bInScaleToContent;
}
