// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Renderer/Widgets/Samples/HorizontalBoxWidget.h"

FHorizontalBoxWidget::FHorizontalBoxWidget(IWidgetManagementInterface* InWidgetManagementInterface, const std::string& InWidgetName, const int InWidgetOrder)
	: FWidget(InWidgetManagementInterface, InWidgetName, InWidgetOrder)
	, HorizontalBoxAlignMethod(EHorizontalBoxAlignMethod::FromTheLeft)
	, bScaleToContent(false)
	, CurrentlyCalculatedNumberOfWidgets(0)
{
	// This is handled by VerticalBox so we do not need to do it
	SetShouldChangeSizeOnChildChange(false);
}

void FHorizontalBoxWidget::ReCalculate()
{
	Super::ReCalculate();

	AlignWidgets(true);
}

void FHorizontalBoxWidget::OnAnyChildChanged()
{
	Super::OnAnyChildChanged();

	// @TODO Could be queued to be done on end of tick as adding many widget may be very slow
	AlignWidgets();
}

void FHorizontalBoxWidget::OnChildSizeChanged()
{
	Super::OnChildSizeChanged();

	// @TODO Could be queued to be done on end of tick as adding many widget may be very slow
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
	const FVector2D<int> VerticalBoxLocation = GetWidgetLocation(EWidgetOrientation::Relative);
	const FVector2D<int> VerticalBoxSize = GetWidgetSize();

	const FVector2D<int> VerticalBoxMaxBounds = VerticalBoxLocation + VerticalBoxSize;

	if (bScaleToContent)
	{
		FVector2D<int> VerticalBoxSizeCalculated = { 0, 0 };

		// Calculate size for parent widget
		for (ContainerInt i = 0; i < ManagedWidgets.Size(); i++)
		{
			const FWidget* ChildWidget = ManagedWidgets[i];

			// We must ensure it's only done when it should be visible
			if (ChildWidget->IsVisible())
			{
				const FVector2D<int> ChildWidgetSize = ChildWidget->GetWidgetSize();

				// Find child with the biggest width
				if (ChildWidgetSize.Y > VerticalBoxSizeCalculated.Y)
				{
					VerticalBoxSizeCalculated.Y = ChildWidgetSize.Y;
				}

				// Always add height
				VerticalBoxSizeCalculated.X += ChildWidgetSize.X;
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
			NewChildLocation.X += AggregatedChildSizeLast.X;

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

			AggregatedChildSizeLast.X += ChildWidgetSize.X;

			ChildWidget->RefreshWidget();
		}
	}
}

void FHorizontalBoxWidget::SetScaleToContent(const bool bInScaleToContent)
{
	bScaleToContent = bInScaleToContent;
}
