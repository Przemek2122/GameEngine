// Created by Przemysław Wiewióra 2020

#include "CoreEngine.h"
#include "Renderer/Widgets/Samples/VerticalBoxWidget.h"

FVerticalBoxWidget::FVerticalBoxWidget(IWidgetManagementInterface* InWidgetManagementInterface, const std::string& InWidgetName, const int InWidgetOrder)
	: FWidget(InWidgetManagementInterface, InWidgetName, InWidgetOrder)
	, VerticalBoxAlignMethod(EVerticalBoxAlignMethod::AlignToCenter)
	, bScaleToContent(true)
{
	// This is handled by VerticalBox so we do not need to do it
	SetShouldChangeSizeOnChildChange(false);
}

void FVerticalBoxWidget::RebuildWidget()
{
	Super::RebuildWidget();

	AlignWidgets();
}

void FVerticalBoxWidget::SetScaleToContent(const bool bNewScaleToContent)
{
	bScaleToContent = bNewScaleToContent;
}

void FVerticalBoxWidget::AlignWidgets()
{
	if (bScaleToContent)
	{
		SetWidgetSize(GetDesiredWidgetGeometry().Size, true);
	}

	switch (VerticalBoxAlignMethod)
	{
		case EVerticalBoxAlignMethod::AlignToLeft:
		{
			AlignToLeft();

			break;
		}
		case EVerticalBoxAlignMethod::AlignToCenter:
		{
			AlignToCenter();

			break;
		}
	}

	UpdateAnchor();
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

void FVerticalBoxWidget::AlignToLeft()
{
	const FVector2D<int> VerticalBoxLocation = GetWidgetLocation(EWidgetOrientation::Relative);
	const FVector2D<int> VerticalBoxSize = GetWidgetSize();
	const FVector2D<int> VerticalBoxMaxBounds = VerticalBoxLocation + VerticalBoxSize;
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

			ChildWidget->SetWidgetLocation(NewChildLocation, EWidgetOrientation::Relative, true, true);

			AggregatedChildSizeLast.Y += ChildWidgetSize.Y;
		}
	}
}

void FVerticalBoxWidget::AlignToCenter()
{
	const FVector2D<int> VerticalBoxLocation = GetWidgetLocation(EWidgetOrientation::Relative);
	const FVector2D<int> VerticalBoxSize = GetWidgetSize();
	const FVector2D<int> VerticalBoxMaxBounds = VerticalBoxLocation + VerticalBoxSize;
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

			// Make sure it's in center horizontally
			NewChildLocation.X = (VerticalBoxSize.X - ChildWidgetSize.X) / 2;

			ChildWidget->SetWidgetLocation(NewChildLocation, EWidgetOrientation::Relative, true, true);

			AggregatedChildSizeLast.Y += ChildWidgetSize.Y;
		}
	}

	RequestWidgetRebuild();
}
