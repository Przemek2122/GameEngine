// See https://github.com/Przemek2122/GameEngine

#include "CoreEngine.h"
#include "Renderer/Widgets/WidgetsPositionInterface.h"

#include "Misc/Math.h"

IWidgetPositionInterface::IWidgetPositionInterface(IWidgetManagementInterface* InWidgetManagementInterface)
	: WidgetSizeType(EWidgetSizeType::Pixels)
	, DefaultAnchor(EAnchor::Center)
	, CurrentAnchor(EAnchor::None)
	, ClippingMethodInterface(EClipping::Cut)
	, bShouldChangeSizeToFitChildren(true)
{
}

void IWidgetPositionInterface::GenerateWidgetGeometry(FWidgetGeometry& InWidgetGeometry)
{
	GenerateChildWidgetGeometry();

	const FWidgetMargin& CurrentPadding = GetWidgetMargin();
	InWidgetGeometry.Size = GetWidgetSize() + CurrentPadding.GetSize();

	Super::GenerateWidgetGeometry(InWidgetGeometry);
}

void IWidgetPositionInterface::GenerateDesiredWidgetGeometry()
{
	// Default alignment is like VerticalBox
	const CArray<FWidgetGeometry>& ChildrenGeometryRef = GetChildrenGeometry();
	for (const FWidgetGeometry& Geometry : ChildrenGeometryRef)
	{
		DesiredWidgetGeometry.Size.Y += Geometry.Size.Y;

		if (Geometry.Size.X > DesiredWidgetGeometry.Size.X)
		{
			DesiredWidgetGeometry.Size.X = Geometry.Size.X;
		}
	}
}

void IWidgetPositionInterface::RebuildWidget()
{
	GenerateChildWidgetGeometry();

	Super::RebuildWidget();
}

FVector2D<int32> IWidgetPositionInterface::GetWidgetLocation(const EWidgetOrientation WidgetOrientation) const
{
	switch (WidgetOrientation)
	{
		case EWidgetOrientation::Absolute:
		{
			return WidgetLocationInterface;
		}
		case EWidgetOrientation::Relative:
		{
			return WidgetLocationInterface - GetWidgetManagerOffset();
		}
	}

	return { };
}

void IWidgetPositionInterface::SetWidgetLocation(const FVector2D<int32> InWidgetLocation, const EWidgetOrientation WidgetOrientation, const bool bSetNoneAnchor, const bool bWasSentFromRebuild)
{
	switch (WidgetOrientation)
	{
		case EWidgetOrientation::Absolute:
		{
			WidgetLocationInterface = InWidgetLocation;

			break;
		}
		case EWidgetOrientation::Relative:
		{
			WidgetLocationInterface = GetParent()->GetWidgetManagerOffset() + InWidgetLocation;

			break;
		}
	}

	if (bSetNoneAnchor)
	{
		SetAnchor(EAnchor::None);
	}

	if (!bWasSentFromRebuild)
	{
		RequestWidgetRebuild();
	}

	UpdateWidgetLocation();
}

FVector2D<int32> IWidgetPositionInterface::GetWidgetSize() const
{
	return WidgetSizeInPixelsInterface;
}

void IWidgetPositionInterface::SetWidgetSize(const FVector2D<int32> InWidgetSize, const bool bWasSentFromRebuild)
{
	WidgetSizeType = EWidgetSizeType::Pixels;
	WidgetSizeInPixelsInterface = InWidgetSize;

	bShouldChangeSizeToFitChildren = false;

	UpdateAnchor();
	UpdateWidgetSize();

	if (HasParent())
	{
		GetParent()->OnChildSizeChanged();
	}

	if (!bWasSentFromRebuild)
	{
		RequestWidgetRebuild();
	}
}

void IWidgetPositionInterface::SetWidgetSizePercent(const FVector2D<float> InScreenPercentage)
{
	WidgetSizeType = EWidgetSizeType::ParentPercentage;

	WidgetSizeInScreenPercentInterface = InScreenPercentage;

	UpdateSizeInPercent();

	UpdateAnchor();

	UpdateWidgetSize();

	if (HasParent())
	{
		GetParent()->OnChildSizeChanged();
	}
}

void IWidgetPositionInterface::UpdateWidgetLocation()
{

	RefreshWidgetLocationForChildren();
}

void IWidgetPositionInterface::UpdateWidgetSize()
{
	switch (WidgetSizeType)
	{
		case EWidgetSizeType::Pixels:
		{
			UpdateWidgetSizePixels();

			break;
		}
		case EWidgetSizeType::ParentPercentage:
		{
			UpdateSizeInPercent();
			break;
		}
	}

	RefreshWidgetSizeForChildren();
}

void IWidgetPositionInterface::UpdateAnchor()
{
	switch (CurrentAnchor)
	{
		case EAnchor::None:
		{
			// This option means user do not want to use Anchor system.
			break;
		}
		
		case EAnchor::Center:
		{
			const FVector2D<int> ParentSize = GetParent()->GetWidgetManagerSize();
			const FVector2D<int> ThisWidgetSize = GetWidgetSize();
			
			FVector2D<int> RelativeCenter;

			RelativeCenter.X = (ParentSize.X - ThisWidgetSize.X) / 2;
			RelativeCenter.Y = (ParentSize.Y - ThisWidgetSize.Y) / 2;
			
			SetWidgetLocation(RelativeCenter, EWidgetOrientation::Relative, false);
			break;
		}
		
		case EAnchor::LeftTop:
		{
			SetWidgetLocation(0, EWidgetOrientation::Absolute, false);
			break;
		}
		
		case EAnchor::LeftBottom:
		{
			const FVector2D<int> ParentSize = GetParent()->GetWidgetManagerSize();
			const FVector2D<int> ThisWidgetSize = GetWidgetSize();
		
			FVector2D<int> RelativeCenter;
			
			RelativeCenter.X = 0;
			RelativeCenter.Y = ParentSize.Y - ThisWidgetSize.Y;
			
			SetWidgetLocation(RelativeCenter, EWidgetOrientation::Relative, false);
			break;
		}
		
		case EAnchor::RightTop:
		{
			const FVector2D<int> ParentSize = GetParent()->GetWidgetManagerSize();
			const FVector2D<int> ThisWidgetSize = GetWidgetSize();
		
			FVector2D<int> RelativeCenter;
			
			RelativeCenter.X = ParentSize.X - ThisWidgetSize.X;
			RelativeCenter.Y = 0;
			
			SetWidgetLocation(RelativeCenter, EWidgetOrientation::Relative, false);
			break;
		}
		
		case EAnchor::RightBottom:
		{
			const FVector2D<int> ParentSize = GetParent()->GetWidgetManagerSize();
			const FVector2D<int> ThisWidgetSize = GetWidgetSize();
		
			FVector2D<int> RelativeCenter;
			
			RelativeCenter.X = ParentSize.X - ThisWidgetSize.X;
			RelativeCenter.Y = ParentSize.Y - ThisWidgetSize.Y;
			
			SetWidgetLocation(RelativeCenter, EWidgetOrientation::Relative, false);
			break;
		}
		
		case EAnchor::TopCenter:
		{
			const FVector2D<int> ParentSize = GetParent()->GetWidgetManagerSize();
			const FVector2D<int> ThisWidgetSize = GetWidgetSize();
		
			FVector2D<int> RelativeCenter;
			
			RelativeCenter.X = (ParentSize.X - ThisWidgetSize.X) / 2;
			RelativeCenter.Y = 0;
			
			SetWidgetLocation(RelativeCenter, EWidgetOrientation::Relative, false);
			break;
		}
		
		case EAnchor::LeftCenter:
		{
			const FVector2D<int> ParentSize = GetParent()->GetWidgetManagerSize();
			const FVector2D<int> ThisWidgetSize = GetWidgetSize();
		
			FVector2D<int> RelativeCenter;
			
			RelativeCenter.X = 0;
			RelativeCenter.Y = (ParentSize.Y - ThisWidgetSize.Y) / 2;
			
			SetWidgetLocation(RelativeCenter, EWidgetOrientation::Relative, false);
			break;
		}
		
		case EAnchor::BottomCenter:
		{
			const FVector2D<int> ParentSize = GetParent()->GetWidgetManagerSize();
			const FVector2D<int> ThisWidgetSize = GetWidgetSize();
		
			FVector2D<int> RelativeCenter;
			
			RelativeCenter.X = (ParentSize.X - ThisWidgetSize.X) / 2;
			RelativeCenter.Y = ParentSize.Y - ThisWidgetSize.Y;
			
			SetWidgetLocation(RelativeCenter, EWidgetOrientation::Relative, false);
			break;
		}
		
		case EAnchor::RightCenter:
		{
			const FVector2D<int> ParentSize = GetParent()->GetWidgetManagerSize();
			const FVector2D<int> ThisWidgetSize = GetWidgetSize();
		
			FVector2D<int> RelativeCenter;
			
			RelativeCenter.X = ParentSize.X - ThisWidgetSize.X;
			RelativeCenter.Y = (ParentSize.Y - ThisWidgetSize.Y) / 2;
			
			SetWidgetLocation(RelativeCenter, EWidgetOrientation::Relative, false);
			break;
		}
	}

	UpdateAnchorForChildren();
}

void IWidgetPositionInterface::SetDefaultAnchor(const EAnchor NewAnchor)
{
	if (DefaultAnchor != NewAnchor)
	{
		DefaultAnchor = NewAnchor;
	}
}

void IWidgetPositionInterface::SetAnchor(const EAnchor NewAnchor)
{
	if (CurrentAnchor != NewAnchor)
	{
		CurrentAnchor = NewAnchor;

		UpdateAnchor();
	}
}

EAnchor IWidgetPositionInterface::GetAnchor() const
{
	return CurrentAnchor;
}

void IWidgetPositionInterface::SetClippingMethod(const EClipping NewClippingMethod)
{
	if (ClippingMethodInterface != NewClippingMethod)
	{
		OnClippingMethodChanged(NewClippingMethod);

		ClippingMethodInterface = NewClippingMethod;
	}
}

EClipping IWidgetPositionInterface::GetClippingMethod() const
{
	return ClippingMethodInterface;
}

void IWidgetPositionInterface::SetWidgetMargin(const FWidgetMargin& InWidgetMargin)
{
	WidgetMargin = InWidgetMargin;
}

std::string IWidgetPositionInterface::GetName() const
{
	static const std::string DefaultWidgetName = "DefaultWidgetNameInInterface";

	return DefaultWidgetName;
}

void IWidgetPositionInterface::OnClippingMethodChanged(EClipping NewClippingMethod)
{
}

void IWidgetPositionInterface::RefreshWidgetSizeForChildren()
{
	for (FWidget* Widget : ManagedWidgets)
	{
		Widget->UpdateWidgetSize();
	}
}

void IWidgetPositionInterface::RefreshWidgetLocationForChildren()
{
	for (FWidget* Widget : ManagedWidgets)
	{
		Widget->UpdateWidgetLocation();
	}
}

void IWidgetPositionInterface::UpdateAnchorForChildren()
{
	for (FWidget* Widget : ManagedWidgets)
	{
		Widget->UpdateAnchor();
	}
}

void IWidgetPositionInterface::UpdateLocation()
{
	UpdateAnchor();
}

void IWidgetPositionInterface::UpdateSizeInPercent()
{
	if (WidgetSizeType == EWidgetSizeType::ParentPercentage)
	{
		const FVector2D<int> ParentSize = GetParent()->GetWidgetManagerSize();

		WidgetSizeInPixelsInterface.X = FMath::RoundToInt(static_cast<float>(ParentSize.X) * WidgetSizeInScreenPercentInterface.X);
		WidgetSizeInPixelsInterface.Y = FMath::RoundToInt(static_cast<float>(ParentSize.Y) * WidgetSizeInScreenPercentInterface.Y);
	}
}

void IWidgetPositionInterface::UpdateWidgetSizePixels()
{
	switch (ClippingMethodInterface)
	{
	case EClipping::None:
	{
		break;
	}

	case EClipping::Resize:
	{
		const FVector2D<int> ParentSize = GetWidgetManagerSize();

		if (ParentSize.X < WidgetSizeInPixelsInterface.X)
		{
			WidgetSizeInPixelsInterface.X = ParentSize.X;
		}

		if (ParentSize.Y < WidgetSizeInPixelsInterface.Y)
		{
			WidgetSizeInPixelsInterface.Y = ParentSize.Y;
		}

		break;
	}
	case EClipping::Cut:
	{
		const FVector2D<int> ParentSize = GetWidgetManagerSize();

		if (ParentSize.X < WidgetSizeInPixelsInterface.X)
		{
			WidgetSizeInPixelsInterface.X = ParentSize.X;
		}

		if (ParentSize.Y < WidgetSizeInPixelsInterface.Y)
		{
			WidgetSizeInPixelsInterface.Y = ParentSize.Y;
		}

		break;
	}
	}
}

void IWidgetPositionInterface::GenerateChildWidgetGeometry()
{
	const bool bAnyChanged = RebuildChildren();
	if (bAnyChanged)
	{
		ChildrenGeometry.Clear();

		for (FWidget* ManagedWidget : ManagedWidgets)
		{
			FWidgetGeometry ChildWidgetGeometry;
			ManagedWidget->GenerateWidgetGeometry(ChildWidgetGeometry);

			ChildrenGeometry.Push(ChildWidgetGeometry);
		}

		DesiredWidgetGeometry = FWidgetGeometry();

		// When we have children size we can create desired geometry
		GenerateDesiredWidgetGeometry();
	}
}

bool IWidgetPositionInterface::RebuildChildren()
{
	bool bAnyChildChanged = false;

	for (FWidget* ManagedWidget : ManagedWidgets)
	{
		if (ManagedWidget->NeedsWidgetRebuild())
		{
			ManagedWidget->RebuildWidget();

			bAnyChildChanged = true;
		}
	}

	return bAnyChildChanged;
}
