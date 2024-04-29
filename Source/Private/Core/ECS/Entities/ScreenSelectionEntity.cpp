#include "CoreEngine.h"
#include "ECS/Entities/ScreenSelectionEntity.h"
#include "ECS/Interfaces/ScreenSelectionInterface.h"
#include "Input/EventHandler.h"

EScreenSelectionEntity::EScreenSelectionEntity(FEntityManager* InEntityManager)
	: EEntity(InEntityManager)
	, bIsSelecting(false)
	, ClickInsteadOfSelectionTolerance(10.f)
{
}

void EScreenSelectionEntity::EndPlay()
{
	OnEndPlay.Execute();

	EEntity::EndPlay();
}

void EScreenSelectionEntity::RegisterScreenSelectable(IScreenSelectionInterface* InScreenSelectable)
{
	ScreenSelectableObjects.Push(InScreenSelectable);
}

void EScreenSelectionEntity::UnRegisterScreenSelectable(IScreenSelectionInterface* InScreenSelectable)
{
	ScreenSelectableObjects.Remove(InScreenSelectable);
}

void EScreenSelectionEntity::OnMouseMove(FVector2D<int> InMousePosition, EInputState)
{
	if (bIsSelecting)
	{
		const FVector2D<int> SelectionEnd = InMousePosition;

		for (int i = 0; i < ScreenSelectableObjects.Size(); i++)
		{
			IScreenSelectionInterface* ScreenSelectable = ScreenSelectableObjects[i]; 

			const FVector2D<int> ScreenSelectableLocation = ScreenSelectable->GetLocation();
			const FVector2D<int> ScreenSelectableSize = ScreenSelectable->GetSize();

			const bool bIsSelectedHorizontalToRight =	SelectionStart.X >= ScreenSelectableLocation.X &&
														SelectionEnd.X <= ScreenSelectableLocation.X + ScreenSelectableSize.X;

			const bool bIsSelectedHorizontalToLeft =	SelectionEnd.X >= ScreenSelectableLocation.X &&
														SelectionStart.X <= ScreenSelectableLocation.X + ScreenSelectableSize.X;

			const bool bIsSelectedVerticalToDown =		SelectionEnd.Y >= ScreenSelectableLocation.Y &&
														SelectionStart.Y <= ScreenSelectableLocation.Y + ScreenSelectableSize.Y;

			const bool bIsSelectedVerticalToUp =		SelectionStart.Y >= ScreenSelectableLocation.Y &&
														SelectionEnd.Y <= ScreenSelectableLocation.Y + ScreenSelectableSize.Y;

			if ((bIsSelectedHorizontalToRight || bIsSelectedHorizontalToLeft) && (bIsSelectedVerticalToDown || bIsSelectedVerticalToUp))
			{
				ScreenSelectable->NativeSelect();

				AddToCurrentlySelectedObjects(ScreenSelectable);
			}
			else
			{
				ScreenSelectable->NativeDeselect();

				RemoveFromCurrentlySelectedObjects(ScreenSelectable);
			}
		}
	}
}

void EScreenSelectionEntity::OnMouseLeftClick(FVector2D<int> InMousePosition, EInputState InputState)
{
	switch (InputState)
	{
		case EInputState::PRESS:
		{
			SelectionStart = InMousePosition;

			OnStartSelecting();

			break;
		}

		case EInputState::RELEASE:
		{
			OnEndSelecting();

			if (SelectionStart.DistanceTo(InMousePosition) < ClickInsteadOfSelectionTolerance)
			{
				OnClickInsteadOfSelection();
			}

			break;
		}

		default:
		{
			LOG_ERROR("EScreenSelectionEntity::OnMouseLeftClick: Unknown InputState");
		}
	}
}

void EScreenSelectionEntity::OnStartSelecting()
{
	bIsSelecting = true;
}

void EScreenSelectionEntity::OnEndSelecting()
{
	bIsSelecting = false;
}

void EScreenSelectionEntity::OnClickInsteadOfSelection()
{
	LOG_INFO("Click instead of selection");
}

const CArray<IScreenSelectionInterface*>& EScreenSelectionEntity::GetCurrentlySelectedObjects() const
{
	return CurrentlySelectedObjects;
}

void EScreenSelectionEntity::RegisterInput(const FEventHandler* InputHandler)
{
	// Bind input
	InputHandler->MouseDelegates.Move->Delegate.BindObject(this, &EScreenSelectionEntity::OnMouseMove);
	InputHandler->MouseDelegates.LeftButton->Delegate.BindObject(this, &EScreenSelectionEntity::OnMouseLeftClick);
}

void EScreenSelectionEntity::UnRegisterInput(const FEventHandler* InputHandler)
{
	// Input must be unregistered, otherwise it might be called after the entity is destroyed
	InputHandler->MouseDelegates.Move->Delegate.UnBindObject(this, &EScreenSelectionEntity::OnMouseMove);
	InputHandler->MouseDelegates.LeftButton->Delegate.UnBindObject(this, &EScreenSelectionEntity::OnMouseLeftClick);
}

void EScreenSelectionEntity::AddToCurrentlySelectedObjects(IScreenSelectionInterface* InScreenSelectable)
{
	CurrentlySelectedObjects.Push(InScreenSelectable);
}

void EScreenSelectionEntity::RemoveFromCurrentlySelectedObjects(IScreenSelectionInterface* InScreenSelectable)
{
	CurrentlySelectedObjects.Remove(InScreenSelectable);
}
