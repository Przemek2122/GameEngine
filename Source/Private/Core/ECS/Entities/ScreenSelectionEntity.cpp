#include "CoreEngine.h"
#include "ECS/Entities/ScreenSelectionEntity.h"
#include "ECS/Interfaces/ScreenSelectionInterface.h"
#include "Input/EventHandler.h"
#include "Renderer/Map/Map.h"

EScreenSelectionEntity::EScreenSelectionEntity(FEntityManager* InEntityManager)
	: EEntity(InEntityManager)
	, bIsSelecting(false)
	, ClickInsteadOfSelectionTolerance(2.f)
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
		CheckScreenSelection(InMousePosition);
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
				OnClickInsteadOfSelection(InMousePosition);
			}

			break;
		}

		default:
		{
			LOG_ERROR("EScreenSelectionEntity::OnMouseLeftClick: Unknown InputState");
		}
	}
}

void EScreenSelectionEntity::OnMouseRightClick(FVector2D<int> InMousePosition, EInputState InputState)
{
	switch (InputState)
	{
		case EInputState::PRESS:
		{
			FMap* CurrentMap = GetCurrentMap();
			if (CurrentMap != nullptr)
			{
				for (IScreenSelectionInterface* CurrentlySelectedObject : CurrentlySelectedObjects)
				{
					FVector2D<int> MapRenderOffset = CurrentMap->GetMapRenderOffset();

					CurrentlySelectedObject->NativeDoAction(InMousePosition - MapRenderOffset);
				}
			}

			break;
		}

		default:
		{
			LOG_WARN("Got default case.");
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

void EScreenSelectionEntity::OnClickInsteadOfSelection(const FVector2D<int>& InMousePosition)
{
	// Update position as 
	SelectionStart = InMousePosition;

	CheckScreenSelection(InMousePosition);
}

const CArray<IScreenSelectionInterface*>& EScreenSelectionEntity::GetCurrentlySelectedObjects() const
{
	return CurrentlySelectedObjects;
}

void EScreenSelectionEntity::RegisterInput(FEventHandler* InputHandler)
{
	// Bind input
	InputHandler->MouseDelegates.GetMouseDelegateByName("MOUSE_MOVE")->Delegate.BindObject(this, &EScreenSelectionEntity::OnMouseMove);
	InputHandler->MouseDelegates.GetMouseDelegateByName("MOUSE_BUTTON_LEFT")->Delegate.BindObject(this, &EScreenSelectionEntity::OnMouseLeftClick);
	InputHandler->MouseDelegates.GetMouseDelegateByName("MOUSE_BUTTON_RIGHT")->Delegate.BindObject(this, &EScreenSelectionEntity::OnMouseRightClick);
}

void EScreenSelectionEntity::UnRegisterInput(FEventHandler* InputHandler)
{
	// Input must be unregistered, otherwise it might be called after the entity is destroyed
	InputHandler->MouseDelegates.GetMouseDelegateByName("MOUSE_MOVE")->Delegate.UnBindObject(this, &EScreenSelectionEntity::OnMouseMove);
	InputHandler->MouseDelegates.GetMouseDelegateByName("MOUSE_BUTTON_LEFT")->Delegate.UnBindObject(this, &EScreenSelectionEntity::OnMouseLeftClick);
	InputHandler->MouseDelegates.GetMouseDelegateByName("MOUSE_BUTTON_RIGHT")->Delegate.UnBindObject(this, &EScreenSelectionEntity::OnMouseRightClick);
}

void EScreenSelectionEntity::CheckScreenSelection(const FVector2D<int>& InMousePosition)
{
	const FVector2D<int> SelectionEnd = InMousePosition;

	CurrentlySelectedObjects.Clear();

	for (int i = 0; i < ScreenSelectableObjects.Size(); i++)
	{
		IScreenSelectionInterface* ScreenSelectable = ScreenSelectableObjects[i];

		const FVector2D<int> ScreenSelectableLocation = ScreenSelectable->GetLocation();
		const FVector2D<int> ScreenSelectableSize = ScreenSelectable->GetSize();

		const bool bIsSelectedHorizontalToRight = SelectionStart.X >= ScreenSelectableLocation.X &&
			SelectionEnd.X <= ScreenSelectableLocation.X + ScreenSelectableSize.X;

		const bool bIsSelectedHorizontalToLeft = SelectionEnd.X >= ScreenSelectableLocation.X &&
			SelectionStart.X <= ScreenSelectableLocation.X + ScreenSelectableSize.X;

		const bool bIsSelectedVerticalToDown = SelectionEnd.Y >= ScreenSelectableLocation.Y &&
			SelectionStart.Y <= ScreenSelectableLocation.Y + ScreenSelectableSize.Y;

		const bool bIsSelectedVerticalToUp = SelectionStart.Y >= ScreenSelectableLocation.Y &&
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

void EScreenSelectionEntity::AddToCurrentlySelectedObjects(IScreenSelectionInterface* InScreenSelectable)
{
	CurrentlySelectedObjects.Push(InScreenSelectable);
}

void EScreenSelectionEntity::RemoveFromCurrentlySelectedObjects(IScreenSelectionInterface* InScreenSelectable)
{
	CurrentlySelectedObjects.Remove(InScreenSelectable);
}
