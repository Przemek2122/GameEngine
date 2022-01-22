// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Renderer/Widgets/Samples/VerticalBoxWidget.h"

FVerticalBoxWidget::FVerticalBoxWidget(IWidgetManagementInterface* InWidgetManagementInterface, const std::string& InWidgetName, const int InWidgetOrder)
	: FWidget(InWidgetManagementInterface, InWidgetName, InWidgetOrder)
{
}

void FVerticalBoxWidget::Render()
{
#if _DEBUG
	GetRenderer()->DrawRectangle(GetWidgetLocationAbsolute(), GetWidgetSize(), FColorRGBA::ColorPink());
#endif
}

void FVerticalBoxWidget::RegisterWidget(FWidget* Widget)
{
	Super::RegisterWidget(Widget);

	AlignWidgets();
}

void FVerticalBoxWidget::UnRegisterWidget(FWidget* Widget)
{
	Super::UnRegisterWidget(Widget);

	AlignWidgets();
}

void FVerticalBoxWidget::AlignWidgets()
{
	switch (VerticalBoxAlignMethod)
	{
		case Default:
		{
			AlignDefault();
			break;
		}
		case Even:
		{
			AlignEven();
			break;
		}
	}
}

void FVerticalBoxWidget::AlignDefault()
{
	const FVector2D<int> VerticalBoxLocation = GetWidgetLocationRelative();
	const FVector2D<int> VerticalBoxSize = GetWidgetSize();

	const FVector2D<int> VerticalBoxMaxBounds = VerticalBoxLocation + VerticalBoxSize;

	FVector2D<int> VerticalBoxLocationLast = {0, 0};
	FVector2D<int> VerticalBoxSizeLast = {0, 0};

	//float TotalHeight = 0.f;
	
	for (size_t i = 0; i < ManagedWidgets.Size(); i++)
	{
		FWidget* ChildWidget = ManagedWidgets[i];

		const FVector2D<int> NewChildLocation = VerticalBoxLocation + VerticalBoxLocationLast;
		
		FVector2D<int> ChildWidgetSize = ChildWidget->GetWidgetSize();
		
		const FVector2D<int> ChildBounds = NewChildLocation + ChildWidgetSize;
		
		// Make sure it fits inside box
		{
			if (ChildBounds.X > VerticalBoxMaxBounds.X)
			{
				ChildWidgetSize.X = VerticalBoxMaxBounds.X;
			}
			
			if (ChildBounds.Y > VerticalBoxMaxBounds.Y)
			{
				ChildWidgetSize.Y = VerticalBoxMaxBounds.Y;
			}
		}

		VerticalBoxLocationLast += VerticalBoxLocation;
		VerticalBoxSizeLast += VerticalBoxSizeLast;
		
		ChildWidget->SetWidgetLocationAbsolute(NewChildLocation);
		ChildWidget->SetWidgetSize(ChildWidgetSize, false);

		ChildWidget->RefreshWidget();
	}
}

void FVerticalBoxWidget::AlignEven()
{
}

void FVerticalBoxWidget::SetVerticalBoxAlignMethod(const EVerticalBoxAlignMethod InVerticalBoxAlignMethod)
{
	VerticalBoxAlignMethod = InVerticalBoxAlignMethod;
}

EVerticalBoxAlignMethod FVerticalBoxWidget::GetVerticalBoxAlignMethod() const
{
	return VerticalBoxAlignMethod;
}
