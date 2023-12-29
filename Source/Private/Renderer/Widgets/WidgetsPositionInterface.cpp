// See https://github.com/Przemek2122/GameEngine

#include "CoreEngine.h"
#include "Renderer/Widgets/WidgetsPositionInterface.h"

#include "SDL/SDL_egl.h"

IWidgetPositionInterface::IWidgetPositionInterface(IWidgetManagementInterface* InWidgetManagementInterface)
	: DefaultAnchorInterface(EAnchor::Center)
	, AnchorInterface(EAnchor::None)
	, ClippingMethodInterface(EClipping::Cut)
{
}

void IWidgetPositionInterface::OnLocationChanged()
{
}

void IWidgetPositionInterface::OnSizeChanged()
{
}

void IWidgetPositionInterface::OnAnchorChanged(const EAnchor NewAnchor)
{
	AnchorInterface = NewAnchor;
	
	RefreshAnchor();
}

FVector2D<int> IWidgetPositionInterface::GetWidgetLocation(EWidgetOrientation WidgetOrientation) const
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

void IWidgetPositionInterface::SetWidgetLocation(const FVector2D<int> InWidgetLocation, EWidgetOrientation WidgetOrientation, const bool bSetNoneAnchor)
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
	
	RefreshWidgetLocation();
}

FVector2D<int> IWidgetPositionInterface::GetWidgetSize() const
{
	return WidgetSizeInterface;
}

void IWidgetPositionInterface::SetWidgetSize(const FVector2D<int> InWidgetSize)
{
	WidgetSizeInterface = InWidgetSize;

	RefreshAnchor();

	RefreshWidgetSize();
}

void IWidgetPositionInterface::RefreshWidgetSize()
{
	switch (ClippingMethodInterface)
	{
	case EClipping::None:
		break;
		
	case EClipping::Resize:
		{
			const FVector2D<int> ParentSize = GetWidgetManagerSize();

			if (ParentSize.X < WidgetSizeInterface.X)
			{
				WidgetSizeInterface.X = ParentSize.X;
			}

			if (ParentSize.Y < WidgetSizeInterface.Y)
			{
				WidgetSizeInterface.Y = ParentSize.Y;
			}
		}
		break;
	case EClipping::Cut:
		{
			const FVector2D<int> ParentSize = GetWidgetManagerSize();

			if (ParentSize.X < WidgetSizeInterface.X)
			{
				WidgetSizeInterface.X = ParentSize.X;
			}

			if (ParentSize.Y < WidgetSizeInterface.Y)
			{
				WidgetSizeInterface.Y = ParentSize.Y;
			}
		}
		break;
	}

	OnRefreshWidgetSize();

	RefreshWidgetSizeChild();
}

void IWidgetPositionInterface::RefreshWidgetLocation()
{
	OnRefreshWidgetLocation();

	RefreshWidgetLocationChild();
}

void IWidgetPositionInterface::RefreshAnchor()
{
	switch (AnchorInterface)
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
}

void IWidgetPositionInterface::SetDefaultAnchor(const EAnchor NewAnchor)
{
	if (DefaultAnchorInterface != NewAnchor)
	{
		DefaultAnchorInterface = NewAnchor;
	}
}

void IWidgetPositionInterface::SetAnchor(const EAnchor NewAnchor)
{
	if (AnchorInterface != NewAnchor)
	{
		OnAnchorChanged(NewAnchor);
	}
}

EAnchor IWidgetPositionInterface::GetAnchor() const
{
	return AnchorInterface;
}

EClipping IWidgetPositionInterface::GetClippingMethod() const
{
	return ClippingMethodInterface;
}

void IWidgetPositionInterface::SetClippingMethod(const EClipping NewClippingMethod)
{
	if (ClippingMethodInterface != NewClippingMethod)
	{
		OnClippingMethodChanged(NewClippingMethod);

		ClippingMethodInterface = NewClippingMethod;
	}
}

void IWidgetPositionInterface::OnClippingMethodChanged(EClipping NewClippingMethod)
{
}

void IWidgetPositionInterface::OnRefreshWidgetSize()
{
}

void IWidgetPositionInterface::OnRefreshWidgetLocation()
{
}

void IWidgetPositionInterface::RefreshWidgetSizeChild()
{
	for (FWidget* Widget : ManagedWidgets)
	{
		Widget->RefreshWidgetSize();
	}
}

void IWidgetPositionInterface::RefreshWidgetLocationChild()
{
	for (FWidget* Widget : ManagedWidgets)
	{
		Widget->RefreshWidgetLocation();
	}
}
